#ifndef _CAMERAENTITY_H_
#define _CAMERAENTITY_H_

#include "entity.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>

class CameraEntity : public Entity
{
    glm::vec4 _viewport;

public:
    CameraEntity();
    virtual ~CameraEntity();

    glm::mat4 getCameraMatrix() const;

    void changeView();
    void moveToTopView();
    void moveToDefaultView();
    void zoom(float amount);

    virtual int getType();

    const glm::vec4& viewport() const;
    void setViewport(const glm::vec4& viewport);

public:
    static const int Type;
};

#endif // _CAMERAENTITY_H_
