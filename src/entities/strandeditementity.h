#ifndef STRANDEDITEMENTITY_H
#define STRANDEDITEMENTITY_H

#include "entity.h"
#include <GL/glextl.h>

class StrandedItemEntity : public Entity
{
    static class Geometry* _worldGeom;
    static GLuint _shader;
public:
    StrandedItemEntity();
    virtual ~StrandedItemEntity();

    virtual void update(float elapsed);
    virtual int getType();

public:
    static const int Type;
};

#endif // STRANDEDITEMENTITY_H
