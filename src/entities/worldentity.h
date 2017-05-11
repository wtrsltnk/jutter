#ifndef _WORLDENTITY_H_
#define _WORLDENTITY_H_

#include "entity.h"
#include "../common/geometry.h"

#include <set>

class WorldEntity : public Entity
{
    static Geometry* _worldGeom;
public:
    WorldEntity();
    virtual ~WorldEntity();

    virtual int getType();

    static glm::vec3 RandomPointOnBeach();

public:
    static const int Type;
};

#endif // _WORLDENTITY_H_
