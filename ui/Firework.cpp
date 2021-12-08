#include "Firework.h"

Firework::Firework(int drag, int weight, int red, int green, int blue):
    m_drag(drag), m_weight(weight),
    m_red(red), m_green(green), m_blue(blue),
    m_particlesFBO1(nullptr), m_particlesFBO2(nullptr),
    m_firstPass(true), m_evenPass(true), m_numParticles(5000)
{
    m_particlesFBO1 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1,
                                            TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBO2 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1,
                                            TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                            TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
}

Firework::~Firework(){

}
