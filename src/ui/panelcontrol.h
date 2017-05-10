#ifndef PANELCONTROL_H
#define PANELCONTROL_H

#include "control.h"

class Panel : public Control
{
public:
    Panel(const std::string& id);
    virtual ~Panel();

    virtual void render(NVGcontext* vg, float scale = 1.0f);

};

#endif // PANELCONTROL_H
