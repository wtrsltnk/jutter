#include "labelcontrol.h"
#include "colors.h"

Label::Label(const std::string &id)
    : Control(id), _textAlignment(TextAlignments::Center)
{
    this->setFontColor(Colors::Bright);
}

Label::~Label()
{ }

void Label::render(NVGcontext* vg, float scale)
{
    nvgSave(vg);

    nvgTranslate(vg, this->_position.x, this->_position.y);
    nvgScale(vg, scale, scale);

    nvgFontSize(vg, this->size().y);
    nvgFontFace(vg, this->fontFamily().c_str());
    nvgFillColor(vg, Colors::ToNvgColor(this->fontColor()));
    switch (this->_textAlignment)
    {
    case TextAlignments::Center: nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE); break;
    case TextAlignments::Bottom: nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_BOTTOM); break;
    case TextAlignments::BottomLeft: nvgTextAlign(vg,NVG_ALIGN_LEFT | NVG_ALIGN_BOTTOM); break;
    case TextAlignments::BottomRight: nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM); break;
    case TextAlignments::Left: nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE); break;
    case TextAlignments::Right: nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE); break;
    case TextAlignments::Top: nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_TOP); break;
    case TextAlignments::TopLeft: nvgTextAlign(vg, NVG_ALIGN_LEFT| NVG_ALIGN_TOP); break;
    case TextAlignments::TopRight: nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP); break;
    }
    nvgText(vg, 0.0f, 0.0f, this->_text.c_str(), NULL);

    nvgRestore(vg);
}

void Label::setTextAlignment(TextAlignments textAlignment)
{
    this->_textAlignment = textAlignment;
}

TextAlignments Label::textAlignment() const
{
    return this->_textAlignment;
}
