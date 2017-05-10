#ifndef FADABLECONTROL_H
#define FADABLECONTROL_H

#include "nanovg.h"
#include "fadeout.h"
#include <string>

class IFadableControl
{
public:
    virtual const std::string& id() const = 0;

    virtual void render(NVGcontext* vg, float scale = 1.0f) = 0;
    virtual void update(float elapsed) = 0;
    virtual bool isDone() = 0;
};

#endif // FADABLECONTROL_H
