#ifndef LABELCONTROL_H
#define LABELCONTROL_H

#include "control.h"
#include "textalignments.h"

class Label : public Control
{
    TextAlignments _textAlignment;
public:
    Label(const std::string& id);
    virtual ~Label();

    virtual void render(NVGcontext* vg, float scale = 1.0f);

    void setTextAlignment(TextAlignments textAlignment);
    TextAlignments textAlignment() const;

};

#endif // LABELCONTROL_H
