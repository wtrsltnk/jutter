#include "postprocesseffect.h"
#include "shader.h"
#include "log.h"

#include <glm/gtc/matrix_transform.hpp>

PostProcessEffect::PostProcessEffect() : _texColorBuffer(0), _geometry(nullptr) { }

PostProcessEffect::~PostProcessEffect() { }

void PostProcessEffect::setup(int width, int height)
{
    this->_width = width;
    this->_height = height;

    glGenTextures(1, &this->_texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, this->_texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenRenderbuffers(1, &this->_rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, this->_rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->_width, this->_height);

    glGenFramebuffers(1, &this->_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->_frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_texColorBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->_rboDepth);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    this->_shader = LoadShaderProgram("effect");

    this->_geometry = Geometry::createQuad(glm::vec2(this->_width, this->_height), this->_shader);

    auto res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (res != GL_FRAMEBUFFER_COMPLETE)
    {
        Log::Current().Error("Framebuffer not complete");
    }
}

void PostProcessEffect::captureBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->_frameBuffer);
}

void PostProcessEffect::capture(std::function<void()> f)
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->_frameBuffer);
    f();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessEffect::endCaptureBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessEffect::renderEffect()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, this->_width, this->_height);
    glBindTexture(GL_TEXTURE_2D, this->_texColorBuffer);
    this->_geometry->render(glm::ortho(0.0f, float(this->_width), 0.0f, float(this->_height)), glm::mat4(1.0f), glm::mat4(1.0f));
    glBindTexture(GL_TEXTURE_2D, 0);
}

void PostProcessEffect::cleanup()
{
    glDeleteRenderbuffers(1, &this->_rboDepth);
    glDeleteFramebuffers(1, &this->_frameBuffer);
}
