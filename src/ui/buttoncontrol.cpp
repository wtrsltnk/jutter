#include "buttoncontrol.h"
#include "colors.h"

Button::Button(const std::string& id)
    : Control(id), _icon(eFontAwesomeIcons::FA_UNDO), _iconFontFamily("fontawesome"),
      _tooltipAlignment(TextAlignments::Right)
{
    this->setColor(Colors::Secondary);
    this->setFontColor(Colors::Bright);
    this->setBorderColor(Colors::Dark);
    this->setSize(glm::vec2(60.0f, 60.0f));
}

Button::~Button()
{ }

glm::vec2 Button::getEffectivePosition() const
{
    return this->position() - (this->size() / 2.0f);
}

void Button::setIconFontFamily(const std::string& font)
{
    this->_iconFontFamily = font;
}

const std::string& Button::iconFontFamily() const
{
    return this->_iconFontFamily;
}

void Button::setIcon(eFontAwesomeIcons icon)
{
    this->_icon = icon;
}

const eFontAwesomeIcons Button::icon() const
{
    return this->_icon;
}

void Button::setTooltipAlignment(TextAlignments alignment)
{
    this->_tooltipAlignment = alignment;
}

const TextAlignments Button::tooltipAlignment() const
{
    return this->_tooltipAlignment;
}

void Button::render(NVGcontext* vg, float scale)
{
    nvgSave(vg);

    nvgTranslate(vg, this->_position.x, this->_position.y);

    nvgScale(vg, scale * this->_scale, scale * this->_scale);

    if (this->_scale != 1.0f)
    {
        nvgBeginPath(vg);
        nvgRect(vg, -(this->size().x / 2.0f) + 4.0f, -(this->size().y / 2.0f) + 4.0f, this->size().x - 2.0f, this->size().y - 2.0f);
        nvgFillColor(vg, Colors::ToNvgColor(this->borderColor()));
        nvgFill(vg);
    }

    nvgBeginPath(vg);
    nvgRect(vg, -(this->size().x / 2.0f), -(this->size().y / 2.0f), this->size().x, this->size().y);
    nvgFillColor(vg, Colors::ToNvgColor(this->color()));
    nvgFill(vg);

    char icon[8];
    nvgFontSize(vg, (this->size().x * 0.5f));
    nvgFontFace(vg, this->iconFontFamily().c_str());
    nvgFillColor(vg, Colors::ToNvgColor(this->fontColor()));
    nvgTextAlign(vg,NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgText(vg, 0.0f, 0.0f, cpToUTF8(int(this->_icon), icon), NULL);

    if (this->_scale != 1.0f)
    {
        nvgScale(vg, 1.0f / this->_scale, 1.0f / this->_scale);
        nvgFontSize(vg, 32.0f);
        nvgFontFace(vg, this->fontFamily().c_str());
        nvgFillColor(vg, Colors::ToNvgColor(this->fontColor()));

        switch (this->_tooltipAlignment)
        {
            case TextAlignments::Bottom:
            {
                nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_BOTTOM);
                nvgText(vg, 0.0f, -(this->size().x / 1.5f), this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::BottomLeft:
            {
                nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_BOTTOM);
                nvgText(vg, -(this->size().x / 1.5f), -(this->size().x / 1.5f), this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::BottomRight:
            {
                nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_BOTTOM);
                nvgText(vg, (this->size().x / 1.5f), -(this->size().x / 1.5f), this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::Center:
            {
                nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
                nvgText(vg, 0.0f, (this->size().x / 1.5f), this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::Left:
            {
                nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
                nvgText(vg, -(this->size().x / 1.5f), 0.0f, this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::Right:
            {
                nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
                nvgText(vg, (this->size().x / 1.5f), 0.0f, this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::Top:
            {
                nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_TOP);
                nvgText(vg, 0.0f, (this->size().x / 1.5f), this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::TopLeft:
            {
                nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_TOP);
                nvgText(vg, -(this->size().x / 1.5f), (this->size().x / 1.5f), this->_text.c_str(), NULL);
                break;
            }
            case TextAlignments::TopRight:
            {
                nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
                nvgText(vg, (this->size().x / 1.5f), (this->size().x / 1.5f), this->_text.c_str(), NULL);
                break;
            }
        }
    }

    nvgRestore(vg);
}
