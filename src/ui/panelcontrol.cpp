#include "panelcontrol.h"
#include "colors.h"

Panel::Panel(const std::string &id)
    : Control(id)
{
    this->setColor(Colors::Primary);
    this->setBorderColor(Colors::Dark);
}

Panel::~Panel()
{ }

void Panel::render(NVGcontext* vg, float scale)
{
    nvgSave(vg);

    nvgTranslate(vg, this->position().x, this->position().y);
    nvgScale(vg, scale, scale);

    auto borderRadius = 0.0f;

    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / 2.0f) + 4.0f, -(this->size().y / 2.0f) + 4.0f, this->size().x - 2.0f, this->size().y - 2.0f);
    nvgFillColor(vg, Colors::ToNvgColor(this->borderColor()));
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgRoundedRect(vg, -(this->size().x / 2.0f), -(this->size().y / 2.0f), this->size().x, this->size().y, borderRadius);
    nvgFillColor(vg, Colors::ToNvgColor(this->color()));
    nvgFill(vg);

    nvgRestore(vg);
}
