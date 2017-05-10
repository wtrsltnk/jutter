#ifndef BUTTONCONTROL_H
#define BUTTONCONTROL_H

#include "control.h"
#include "fonts.h"
#include "textalignments.h"

class Button : public Control
{
    eFontAwesomeIcons _icon;
    std::string _iconFontFamily;
    TextAlignments _tooltipAlignment;

public:
    Button(const std::string& id);
    virtual ~Button();

    virtual glm::vec2 getEffectivePosition() const;

    virtual void render(NVGcontext* vg, float scale = 1.0f);

    void setIconFontFamily(const std::string& font);
    const std::string& iconFontFamily() const;

    void setIcon(eFontAwesomeIcons icon);
    const eFontAwesomeIcons icon() const;

    void setTooltipAlignment(TextAlignments alignment);
    const TextAlignments tooltipAlignment() const;
};

#endif // BUTTONCONTROL_H
