#ifndef VIEW_H
#define VIEW_H

#include "GL/glew.h"
#include <qgl.h>
#include <QElapsedTimer>
#include <QTimer>

#include <QGLWidget>

#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr

#include <memory>  // std::unique_ptr

#include "gl/datatype/FBO.h"

#include "Firework.h"

class OpenGLShape;

using namespace CS123::GL;

class View : public QGLWidget {
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:

    QElapsedTimer m_time;
    QTimer m_timer;
    bool m_captureMouse;

    int m_drag;
    int m_weight;
    int m_red;
    int m_green;
    int m_blue;

    void drawBlur();
    void drawParticles();
    void setParticleViewport();

    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);

//    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent *event);

    int m_width;
    int m_height;

    GLuint m_phongProgram;
    GLuint m_textureProgram;
    GLuint m_horizontalBlurProgram;
    GLuint m_verticalBlurProgram;
    GLuint m_particleUpdateProgram;
    GLuint m_particleDrawProgram;
    GLuint m_postProcessingProgram;

    std::unique_ptr<OpenGLShape> m_quad;

    std::unique_ptr<FBO> m_blurFBO1;
    std::unique_ptr<FBO> m_blurFBO2;

    GLuint m_particlesVAO;
    std::shared_ptr<FBO> m_particlesFBO1;
    std::shared_ptr<FBO> m_particlesFBO2;
    std::shared_ptr<FBO> m_particlesFBOfinal;
    bool m_firstPass;
    bool m_evenPass;
    int m_numParticles;

    glm::mat4 m_view, m_projection;

    /** For mouse interaction. */
    float m_angleX, m_angleY, m_zoom;
    QPoint m_prevMousePos;

    float m_delta_time;

    std::unique_ptr<Firework> m_firework;

    glm::vec3 m_spawnPoint;

private slots:
    void setDrag(int drag);
    void setWeight(int weight);
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);

    void onLaunch();
    void tick();
};

#endif // VIEW_H
