#include "strandeditementity.h"
#include "entitymanager.h"
#include "../common/shader.h"

Geometry* StrandedItemEntity::_worldGeom = nullptr;
GLuint StrandedItemEntity::_shader = 0;

StrandedItemEntity::StrandedItemEntity()
{
    if (StrandedItemEntity::_shader == 0)
    {
        StrandedItemEntity::_shader = LoadShaderProgram("strandeditem");
    }
    if (StrandedItemEntity::_worldGeom == nullptr)
    {
        StrandedItemEntity::_worldGeom = Geometry::createQuad2(glm::vec3(50.0f, 50.0f, 0.0f), StrandedItemEntity::_shader);
    }
    this->attachGeometryProperty(StrandedItemEntity::_worldGeom);
}

StrandedItemEntity::~StrandedItemEntity()
{ }

void StrandedItemEntity::update(float elapsed)
{
    auto zoomLevel = Entity::Manager()._camera->getPosition().z;
}

int StrandedItemEntity::getType()
{
    return StrandedItemEntity::Type;
}

const int StrandedItemEntity::Type = 9;
