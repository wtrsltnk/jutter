#include "control.h"
#include "ui.h"

Control::Control(const std::string& id)
    : _id(id), _visible(true), _color(glm::vec4(255, 255, 255, 255)), _scale(1.0f), _fontFamily("sans-bold")
{ }

Control::~Control()
{ }

glm::vec2 Control::getEffectiveSize() const
{
    return this->size();
}

glm::vec2 Control::getEffectivePosition() const
{
    return this->position();
}

void Control::update(float elapsed)
{
    auto s = this->getEffectiveSize();
    auto p = this->getEffectivePosition();
    auto m = UI::Manager().currentMousePos();

    if (m.x >= p.x && m.x <= (p.x+s.x) && m.y <= (p.y+s.y) && m.y >= p.y)
    {
        UI::Manager().setHoverControl(this);
    }
    else if (UI::Manager().hoverControl() == this)
    {
        UI::Manager().setHoverControl(nullptr);
    }

    if (UI::Manager().hoverControl() == this)
    {
        this->_scale += 1.0f * elapsed;
        if (this->_scale > 1.1f) this->_scale = 1.1f;
    }
    else if (this->_scale > 1.0f)
    {
        this->_scale -= 1.0f * elapsed;
        if (this->_scale < 1.0f) this->_scale = 1.0f;
    }
}

const std::string& Control::id() const
{
    return this->_id;
}

void Control::setVisible(bool visible)
{
    this->_visible = visible;
}

bool Control::visible() const
{
    return this->_visible;
}

void Control::setText(const std::string& text)
{
    this->_text = text;
}

const std::string& Control::text() const
{
    return this->_text;
}

void Control::setFontFamily(const std::string& font)
{
    this->_fontFamily = font;
}

const std::string& Control::fontFamily() const
{
    return this->_fontFamily;
}

void Control::setPosition(const glm::vec2& position)
{
    this->_position = position;
}

const glm::vec2& Control::position() const
{
    return this->_position;
}

void Control::setSize(const glm::vec2& size)
{
    this->_size = size;
}

const glm::vec2& Control::size() const
{
    return this->_size;
}

void Control::setPadding(const glm::vec2& padding)
{
    this->_padding = padding;
}

const glm::vec2& Control::padding() const
{
    return this->_padding;
}

void Control::setColor(const glm::vec4& color)
{
    this->_color = color;
}

const glm::vec4& Control::color() const
{
    return this->_color;
}

void Control::setBorderColor(const glm::vec4& color)
{
    this->_borderColor = color;
}

const glm::vec4& Control::borderColor() const
{
    return this->_borderColor;
}

void Control::setFontColor(const glm::vec4& color)
{
    this->_fontColor = color;
}

const glm::vec4& Control::fontColor() const
{
    return this->_fontColor;
}
