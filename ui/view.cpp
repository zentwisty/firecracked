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
    m_size(0), m_weight(0),
    m_red(0), m_green(0), m_blue(0),
    m_width(width()), m_height(height()),
    m_phongProgram(0), m_textureProgram(0), m_horizontalBlurProgram(0), m_verticalBlurProgram(0),
    m_quad(nullptr), m_sphere(nullptr),
    m_blurFBO1(nullptr), m_blurFBO2(nullptr),
    m_particlesFBO1(nullptr), m_particlesFBO2(nullptr),
    m_firstPass(true), m_evenPass(true), m_numParticles(5000),
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

void View::setSize(int value)
{
    m_size = value;
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
    // Print the max FBO dimension.
    GLint maxRenderBufferSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &maxRenderBufferSize);
    std::cout << "Max FBO size: " << maxRenderBufferSize << std::endl;

}

void View::drawBlur() {
    //       [Task 5b] Bind m_blurFBO1
    m_blurFBO1->bind();
    // TODO: [Task 1] Do drawing here!
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_phongProgram);
    GLint viewUniformLoc = glGetUniformLocation(m_phongProgram, "view");
    glUniformMatrix4fv(viewUniformLoc, 1, GL_FALSE, glm::value_ptr(m_view));
    GLint projUniformLoc = glGetUniformLocation(m_phongProgram, "projection");
    glUniformMatrix4fv(projUniformLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
    GLint modelUniformLoc = glGetUniformLocation(m_phongProgram, "model");
    glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::vec3(0.0f, 1.2f, 0.0f))));
    //       [Task 1.5] Call glViewport so that the viewport is the right size
    glViewport(0, 0, m_width, m_height);
    m_quad->draw();
    //       [Task 8] Bind m_blurFBO1's color texture
    //m_blurFBO1->getColorAttachment(0).bind();
    //       [Task 7] Unbind m_blurFBO1 and render a full screen quad
    m_blurFBO1->unbind();
    m_blurFBO2->bind();
    glUseProgram(m_horizontalBlurProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    m_blurFBO1->getColorAttachment(0).bind();
    m_quad->draw();
    m_blurFBO2->unbind();
    //m_blurFBO2->getColorAttachment(0).bind();
    glUseProgram(m_verticalBlurProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    m_blurFBO2->getColorAttachment(0).bind();
    m_quad->draw();
    //       [Task 11] Bind m_blurFBO2

}

void View::drawParticles() {
    /*
    auto prevFBO = m_evenPass ? m_particlesFBO1 : m_particlesFBO2;
    auto nextFBO = m_evenPass ? m_particlesFBO2 : m_particlesFBO1;
    float firstPass = m_firstPass ? 1.0f : 0.0f;
    // TODO [Task 14] Move the particles from prevFBO to nextFBO while updating them

    nextFBO->bind();
    glUseProgram(m_particleUpdateProgram);
    glActiveTexture(GL_TEXTURE0);
    prevFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    prevFBO->getColorAttachment(1).bind();
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "firstPass"), firstPass);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "numParticles"), m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevPos"), 0);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevVel"), 1);
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "dt"), m_delta_time);
    m_quad->draw();

    // TODO [Task 17] Draw the particles from nextFBO

    nextFBO->unbind();
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_particleDrawProgram);
    setParticleViewport();
    glActiveTexture(GL_TEXTURE0);
    nextFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    nextFBO->getColorAttachment(1).bind();
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "numParticles"), m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "pos"), 0);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "vel"), 1);
    glUniform1f(glGetUniformLocation(m_particleDrawProgram, "red"), m_red/255.f);
    glUniform1f(glGetUniformLocation(m_particleDrawProgram, "green"), m_green/255.f);
    glUniform1f(glGetUniformLocation(m_particleDrawProgram, "blue"), m_blue/255.f);
    glBindVertexArray(m_particlesVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3*m_numParticles);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

    m_firstPass = false;
    m_evenPass = !m_evenPass;
    */

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
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "B"), m_size);
    m_quad->draw();
    drawBlur();

    // TODO [Task 17] Draw the particles from nextFBO

    nextFBO->unbind();
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
    glBindVertexArray(m_particlesVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3*m_firework->m_numParticles);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

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
    std::cout<<m_width<<" "<<m_height<<std::endl;
}

void View::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(m_firework != nullptr){
        drawParticles();
    }
    std::cout << "paintGL" << std::endl;
}

void View::resizeGL(int w, int h) {
    m_width = w;
    m_height = h;

    // TODO: [Task 5] Initialize FBOs here, with dimensions m_width and m_height.
    m_blurFBO1 = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);
    m_blurFBO2 = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);
    //       [Task 12] Pass in TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE as the last parameter

//    float ratio = static_cast<QGuiApplication *>(QCoreApplication::instance())->devicePixelRatio();
//    w = static_cast<int>(w / ratio);
//    h = static_cast<int>(h / ratio);
//    glViewport(0, 0, w, h);
}

//void View::mousePressEvent(QMouseEvent *event) {

//}

//void View::mouseMoveEvent(QMouseEvent *event) {
//    // This starter code implements mouse capture, which gives the change in
//    // mouse position since the last mouse movement. The mouse needs to be
//    // recentered after every movement because it might otherwise run into
//    // the edge of the screen, which would stop the user from moving further
//    // in that direction. Note that it is important to check that deltaX and
//    // deltaY are not zero before recentering the mouse, otherwise there will
//    // be an infinite loop of mouse move events.
//    if(m_captureMouse) {
//        int deltaX = event->x() - width() / 2;
//        int deltaY = event->y() - height() / 2;
//        if (!deltaX && !deltaY) return;
//        QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

//        // TODO: Handle mouse movements here
//    }
//}

//void View::mouseReleaseEvent(QMouseEvent *event) {

//}

//void View::keyPressEvent(QKeyEvent *event) {
//    if (event->key() == Qt::Key_Escape) QApplication::quit();

//    // TODO: Handle keyboard presses here
//}

//void View::keyReleaseEvent(QKeyEvent *event) {

//}

void View::onLaunch() {
    std::cout << "size: " << m_size << std::endl;
    std::cout << "weight: " << m_weight << std::endl;
    std::cout << "red: " << m_red << std::endl;
    std::cout << "green: " << m_green << std::endl;
    std::cout << "blue: " << m_blue << std::endl;

    // TODO: SPAWN THE FIREWORK HERE
    m_firework = std::make_unique<Firework>(m_red, m_green, m_blue);
}

void View::tick() {
    // Get the number of seconds since the last tick (variable update rate)
    m_delta_time = m_time.restart() * 0.001f;

    // TODO: DRAW TO THE SCREEN HERE
    std::cout << "Tick" << std::endl;


    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
    std::cout<<width()<<std::endl;
}
