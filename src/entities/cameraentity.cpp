#include "cameraentity.h"

#include <glm/gtc/matrix_transform.hpp>

const int CameraEntity::Type = 5;

glm::mat4 CameraEntity::getCameraMatrix() const
{
    return this->getMatrix();
}

CameraEntity::CameraEntity()
{ }

CameraEntity::~CameraEntity()
{ }

void CameraEntity::changeView()
{ }

void CameraEntity::moveToTopView()
{
    auto m = glm::lookAt(
                glm::vec3(0.0f, 0.0f, -1200.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 0.0f, 0.0f)
                );
    this->setMatrix(m);
}

void CameraEntity::moveToDefaultView()
{ }

void CameraEntity::zoom(float amount)
{
    this->_position.z += amount;
}

int CameraEntity::getType()
{
    return CameraEntity::Type;
}

const glm::vec4& CameraEntity::viewport() const
{
    return this->_viewport;
}

void CameraEntity::setViewport(const glm::vec4& viewport)
{
    this->_viewport = viewport;
}
