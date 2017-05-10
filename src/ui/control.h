#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <glm/glm.hpp>

#include "nanovg.h"

#define OFFSET_ONE_BUTTON (height * 0.07f)
#define OFFSET_TWO_BUTTONS (OFFSET_ONE_BUTTON * 3.0f)
#define OFFSET_THREE_BUTTONS (OFFSET_ONE_BUTTON * 5.0f)

class Control
{
    std::string _id;
    bool _visible;
protected:
    std::string _text;
    std::string _fontFamily;
    glm::vec2 _position;
    glm::vec2 _size;
    glm::vec2 _padding;
    glm::vec4 _color;
    glm::vec4 _borderColor;
    glm::vec4 _fontColor;
    float _scale;

public:
    Control(const std::string& id);
    virtual ~Control();

    virtual glm::vec2 getEffectiveSize() const;
    virtual glm::vec2 getEffectivePosition() const;

    virtual void update(float elapsed);
    virtual void render(NVGcontext* vg, float scale = 1.0f) = 0;

    const std::string& id() const;

    // Only needed for temporary controls
    virtual bool canBeDeleted() const { return false; }

    void setVisible(bool visible);
    bool visible() const;

    void setText(const std::string& text);
    const std::string& text() const;

    void setFontFamily(const std::string& font);
    const std::string& fontFamily() const;

    void setPosition(const glm::vec2& position);
    const glm::vec2& position() const;

    void setSize(const glm::vec2& size);
    const glm::vec2& size() const;

    void setPadding(const glm::vec2& padding);
    const glm::vec2& padding() const;

    void setColor(const glm::vec4& color);
    const glm::vec4& color() const;

    void setBorderColor(const glm::vec4& color);
    const glm::vec4& borderColor() const;

    void setFontColor(const glm::vec4& color);
    const glm::vec4& fontColor() const;
};

#endif // CONTROL_H
