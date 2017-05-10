#include "worldentity.h"

Geometry* WorldEntity::_worldGeom = nullptr;

WorldEntity::WorldEntity()
{
    if (WorldEntity::_worldGeom == nullptr)
    {
        WorldEntity::_worldGeom = Geometry::createTerrain();
    }

    this->attachGeometryProperty(WorldEntity::_worldGeom);
}

WorldEntity::~WorldEntity()
{ }

int WorldEntity::getType()
{
    return WorldEntity::Type;
}

int WorldEntity::Type = 8;
