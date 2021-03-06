#include "view.h"

#include "viewformat.h"
#include <QApplication>
#include <QKeyEvent>
#include <iostream>

#include "cs123_lib/resourceloader.h"
#include "cs123_lib/errorchecker.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>

#include "openglshape.h"
#include "gl/textures/Texture2D.h"
#include "gl/shaders/ShaderAttribLocations.h"

using namespace CS123::GL;

View::View(QWidget *parent) : QGLWidget(ViewFormat(), parent),
    m_time(), m_timer(), m_captureMouse(false),
    m_drag(50), m_weight(10),                   // IF YOU CHANGE THESE DEFAULTS UPDATE THE UI TOO
    m_red(230), m_green(100), m_blue(130),      // IF YOU CHANGE THESE DEFAULTS UPDATE THE UI TOO
    m_density(300), m_trailLength(10),          // IF YOU CHANGE THESE DEFAULTS UPDATE THE UI TOO
    m_width(width()), m_height(height()),
    m_phongProgram(0), m_textureProgram(0), m_horizontalBlurProgram(0), m_verticalBlurProgram(0), m_postProcessingProgram(0),
    m_quad(nullptr),
    m_blurFBO1(nullptr), m_blurFBO2(nullptr),
    m_particlesFBO1(nullptr), m_particlesFBO2(nullptr), m_particlesFBOfinal(nullptr),
    m_firstPass(true), m_evenPass(true), m_numParticles(500),
    m_angleX(-0.5f), m_angleY(0.5f), m_zoom(4.f),
    m_delta_time(0.1f),
    m_firework(nullptr)
{
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor
    if (m_captureMouse) {
        QApplication::setOverrideCursor(Qt::BlankCursor);
    }

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The update loop is implemented using a timer
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));
}

View::~View()
{
    glDeleteVertexArrays(1, &m_particlesVAO);
}

void View::setDrag(int drag)
{
    m_drag = drag;
}

void View::setWeight(int weight)
{
    m_weight = weight;
}

void View::setRed(int red)
{
    m_red = red;
}

void View::setGreen(int green)
{
    m_green = green;
}

void View::setBlue(int blue)
{
    m_blue = blue;
}

void View::setDensity(int density)
{
    m_density = density;
}

void View::setTrailLength(int trailLength)
{
    m_trailLength = trailLength;
}


void View::initializeGL() {

    // All OpenGL initialization *MUST* be done during or after this
    // method. Before this method is called, there is no active OpenGL
    // context and all OpenGL calls have no effect.

    //initialize glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Something is very wrong, glew initialization failed." << std::endl;
    }
    std::cout << "Using GLEW " <<  glewGetString( GLEW_VERSION ) << std::endl;

    // Start a timer that will try to get 60 frames per second (the actual
    // frame rate depends on the operating system and other running programs)
    m_time.start();
    m_timer.start(1000 / 60);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    ResourceLoader::initializeGlew();
    glEnable(GL_DEPTH_TEST);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create shader programs.
    m_phongProgram = ResourceLoader::createShaderProgram(
                ":/shaders/phong.vert", ":/shaders/phong.frag");
    m_textureProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/texture.frag");
    m_horizontalBlurProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/horizontalBlur.frag");
    m_verticalBlurProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/verticalBlur.frag");
    m_particleUpdateProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/particles_update.frag");
    m_particleDrawProgram = ResourceLoader::createShaderProgram(
                ":/shaders/particles_draw.vert", ":/shaders/particles_draw.frag");
    m_postProcessingProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/postProcessing.frag");


    // TODO: [Task 6] Fill in the positions and UV coordinates to draw a fullscreen quad
    // We've already set the vertex attributes for you, so be sure to follow those specifications
    // (triangle strip, 4 vertices, position followed by UVs)
    std::vector<GLfloat> quadData;
    quadData = {-1.f, 1.f, 0.f, 0.f, 1.f,
                -1.f, -1.f, 0.f, 0.f, 0.f,
                1.f, 1.f, 0.f, 1.f, 1.f,
                1.f, -1.f, 0.f, 1.f, 0.f};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();

    // We will use this VAO to draw our particles' triangles.
    // It doesn't need any data associated with it, so we don't have to make a full VAO instance
    glGenVertexArrays(1, &m_particlesVAO);
    // TODO [Task 13] Create m_particlesFBO1 and 2 with std::make_shared
    m_particlesFBO1 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1,
                                            TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBO2 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1,
                                            TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBOfinal = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, \
                                                TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);

    // Print the max FBO dimension.
    GLint maxRenderBufferSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &maxRenderBufferSize);
    std::cout << "Max FBO size: " << maxRenderBufferSize << std::endl;

}

void View::drawBlur() {

    // blur horizontally
    m_blurFBO1->bind();
    glUseProgram(m_horizontalBlurProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    //glUniform1f(glGetUniformLocation(m_horizontalBlurProgram, "supportWidth"), 20);
    glActiveTexture(GL_TEXTURE0);
    m_particlesFBOfinal->getColorAttachment(0).bind();
    m_quad->draw();
    m_blurFBO1->unbind();
    //m_blurFBO2->getColorAttachment(0).bind();


    // blur vertically
    m_blurFBO2->bind();
    glUseProgram(m_verticalBlurProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    //glUniform1f(glGetUniformLocation(m_verticalBlurProgram, "supportWidth"), 20);
    glActiveTexture(GL_TEXTURE0);
    m_blurFBO1->getColorAttachment(0).bind();
    m_quad->draw();
    m_blurFBO2->unbind();


    // post processing
    glUseProgram(m_postProcessingProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    glActiveTexture(GL_TEXTURE0);
    m_particlesFBOfinal->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    m_blurFBO2->getColorAttachment(0).bind();
    glUniform1i(glGetUniformLocation(m_postProcessingProgram, "particleColor"), 0);
    glUniform1i(glGetUniformLocation(m_postProcessingProgram, "blurColor"), 1);
    glUniform1f(glGetUniformLocation(m_postProcessingProgram, "blurIntensity"), 2);
    m_quad->draw();


}

void View::drawParticles() {

    auto prevFBO = m_firework->m_evenPass ? m_firework->m_particlesFBO1 : m_firework->m_particlesFBO2;
    auto nextFBO = m_firework->m_evenPass ? m_firework->m_particlesFBO2 : m_firework->m_particlesFBO1;
    float firstPass = m_firework->m_firstPass ? 1.0f : 0.0f;
    // TODO [Task 14] Move the particles from prevFBO to nextFBO while updating them

    nextFBO->bind();
    glUseProgram(m_particleUpdateProgram);
    glActiveTexture(GL_TEXTURE0);
    prevFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    prevFBO->getColorAttachment(1).bind();
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "firstPass"), firstPass);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "numParticles"), m_firework->m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevPos"), 0);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevVel"), 1);
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "dt"), m_delta_time);
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "B"), 1.f+m_firework->m_drag / 50.f);
    glUniform3f(glGetUniformLocation(m_particleUpdateProgram, "spawnPoint"), \
                m_firework->m_spawnPoint.x, m_firework->m_spawnPoint.y, m_firework->m_spawnPoint.z);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "numLayers"), m_firework->m_numLayers);
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "GMultiplier"), 1.0+m_weight/5);
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "time"), std::rand());
    m_quad->draw();
    nextFBO->unbind();

    // TODO [Task 17] Draw the particles from nextFBO

    m_particlesFBOfinal->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_particleDrawProgram);
    setParticleViewport();
    glActiveTexture(GL_TEXTURE0);
    nextFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    nextFBO->getColorAttachment(1).bind();
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "numParticles"), m_firework->m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "pos"), 0);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "vel"), 1);
    glUniform1f(glGetUniformLocation(m_particleDrawProgram, "red"), m_firework->m_red/255.f);
    glUniform1f(glGetUniformLocation(m_particleDrawProgram, "green"), m_firework->m_green/255.f);
    glUniform1f(glGetUniformLocation(m_particleDrawProgram, "blue"), m_firework->m_blue/255.f);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "numLayers"), m_firework->m_numLayers);


    glBindVertexArray(m_particlesVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3*m_firework->m_numParticles*m_firework->m_numLayers);
    glBindVertexArray(0);

    m_particlesFBOfinal->unbind();

    drawBlur();


    m_firework->m_firstPass = false;
    m_firework->m_evenPass = !m_firework->m_evenPass;

}

// Sets the viewport to ensure that {0,0} is always in the center of the viewport
// in clip space, and to ensure that the aspect ratio is 1:1
void View::setParticleViewport() {
    int maxDim = std::max(m_width, m_height);
    int x = (m_width - maxDim) / 2.0f;
    int y = (m_height - maxDim) / 2.0f;
    glViewport(x, y, maxDim, maxDim);
//    std::cout<<m_width<<" "<<m_height<<std::endl;
}

void View::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(m_firework != nullptr){
        drawParticles();
    }
//    std::cout << "paintGL" << std::endl;
}

void View::resizeGL(int w, int h) {
    m_width = w;
    m_height = h;

    // TODO: [Task 5] Initialize FBOs here, with dimensions m_width and m_height.
    m_particlesFBOfinal = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);
    m_blurFBO1 = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);
    m_blurFBO2 = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);
    //       [Task 12] Pass in TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE as the last parameter

//    float ratio = static_cast<QGuiApplication *>(QCoreApplication::instance())->devicePixelRatio();
//    w = static_cast<int>(w / ratio);
//    h = static_cast<int>(h / ratio);
    glViewport(0, 0, m_width, m_height);
}

void View::mousePressEvent(QMouseEvent *event) {
    // TODO: ONLY WORKS WITH SQUARE VIEWPORTS
    float x =  2 * ((event->x() / static_cast<float>(m_width))  - .5f);
    float y = -2 * ((event->y() / static_cast<float>(m_height)) - .5f);

    glm::vec3 spawnPoint = glm::vec3(x, y, 0.f);
    m_firework = std::make_unique<Firework>(spawnPoint, m_drag, m_weight, m_red, m_green, m_blue, m_density, m_trailLength + 1);
}

void View::tick() {
    // Get the number of seconds since the last tick (variable update rate)
    m_delta_time = m_time.restart() * 0.001f;

    // TODO: DRAW TO THE SCREEN HERE
//    std::cout << "Tick" << std::endl;


    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
//    std::cout<<width()<<std::endl;
}
