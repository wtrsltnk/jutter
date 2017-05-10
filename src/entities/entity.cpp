#include "entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Entity::Entity()
    : _deleted(false), _scale(glm::vec3(1.0f)),
      _geometryProperty(nullptr), _moveTo(false)
{ }

Entity::~Entity()
{ }

void Entity::moveTo(const glm::vec3& pos)
{
    this->_moveToPosition = pos;
    this->_moveTo = true;
}

void Entity::attachGeometryProperty(Geometry* renderable)
{
    this->_geometryProperty = renderable;
}

Geometry* Entity::geometryProperty()
{
    return this->_geometryProperty;
}

void Entity::setMatrix(const glm::mat4& mat)
{
    this->_position = glm::vec3(mat[3].x, mat[3].y, mat[3].z);
    this->_rotation = glm::quat_cast(mat);
}

glm::mat4 Entity::getMatrix() const
{
    return glm::translate(glm::mat4(1.0f), this->_position)
            * glm::toMat4(this->_rotation)
            * glm::scale(glm::mat4(1.0f), this->_scale);
}

const glm::vec3& Entity::getPosition() const
{
    return this->_position;
}

bool Entity::isDeleted() const
{
    return this->_deleted;
}

void Entity::setDeleted(bool deleted)
{
    this->_deleted = deleted;
}

void Entity::update(float elapsed)
{ }

void Entity::render(const glm::mat4& proj, const glm::mat4& view)
{
    if (this->geometryProperty() != nullptr)
    {
        this->geometryProperty()->render(proj, view, this->getMatrix());
    }
}

int Entity::getType()
{
    return Entity::Type;
}

int Entity::Type = 0;
