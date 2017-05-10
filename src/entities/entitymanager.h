#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "cameraentity.h"

#include <vector>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>

#define LEVEL_COUNT 16

class EntityManager
{
    friend class Entity;
    static EntityManager* _instance;
    EntityManager();
    glm::mat4 _lastProj;

public:
    virtual ~EntityManager();

    std::vector<Entity*> entitiesOfType(int type);
    glm::vec2 worldToScreen(const glm::vec3& pos) const;

    void init();
    void update(float elapsed);
    void render(const glm::mat4& proj);
    void changeView();
    void moveToTopView();
    void moveToDefaultView();
    void reset();

    CameraEntity* _camera;
    std::set<Entity*> _entities;
};

#endif // _ENTITYMANAGER_H_
