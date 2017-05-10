#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../common/geometry.h"

#include <set>
#include <vector>
#include <queue>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>

class Entity
{
    bool _deleted;
    Geometry* _geometryProperty;
public:
    Entity();
    virtual ~Entity();

    void setMatrix(const glm::mat4& mat);
    glm::mat4 getMatrix() const;
    const glm::vec3& getPosition() const;

    bool isDeleted() const;
    void setDeleted(bool deleted);

    virtual void update(float elapsed);
    void render(const glm::mat4& proj, const glm::mat4& view);
    
    virtual int getType();

    void moveTo(const glm::vec3& pos);

    glm::vec3 _position;
    glm::quat _rotation;
    glm::vec3 _scale;

    glm::vec3 _linearVelocity;
    glm::vec3 _angularVelocity;

    std::queue<glm::vec3> _moveToQueue;
    glm::vec3 _moveToPosition;
    bool _moveTo;

    void attachGeometryProperty(Geometry* renderable);
    Geometry* geometryProperty();

public:
    static int Type;

public:
    static class EntityManager& Manager();
};

#endif // _ENTITY_H_
