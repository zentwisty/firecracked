#ifndef FIREWORK_H
#define FIREWORK_H

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

using namespace CS123::GL;

class Firework
{
public:
    Firework(int red, int green, int blue);
    ~Firework();

    int m_red;
    int m_green;
    int m_blue;
    GLuint m_particlesVAO;
    std::shared_ptr<FBO> m_particlesFBO1;
    std::shared_ptr<FBO> m_particlesFBO2;
    bool m_firstPass;
    bool m_evenPass;
    int m_numParticles;
};

#endif // FIREWORK_H
