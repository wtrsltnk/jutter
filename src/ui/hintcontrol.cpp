#include "hintcontrol.h"
#include "colors.h"
#include "../common/timer.h"

#include <iostream>

HintControl::HintControl(const std::string& id)
    : Control(id), _state(0),
      _horizontalAlignment(HorizontalAlignments::Left),
      _verticalAlignment(VerticalAligments::Bottom)
{
    this->setSize(glm::vec2(3.3f, 1.3f));
    this->_cloudPosition = glm::vec2(1.0f, 1.0f);
    this->setFontColor(glm::vec4(0.0f, 0.0f, 0.0f, 255.0f));
    this->setFontFamily("handwritten");

    this->reset();
}

HintControl::~HintControl() { }

void HintControl::update(float elapsed)
{
    this->_size.update(elapsed);

    this->_borderColor.a = this->_color.a;
}

void HintControl::render(NVGcontext* vg, float scale)
{
    nvgSave(vg);

    nvgTranslate(vg, this->_position.x, this->_position.y);

    nvgScale(vg, scale * this->_scale, scale * this->_scale);

    this->_sx = this->_size.value() * this->size().x;
    this->_sy = this->_size.value() * this->size().y;
    this->_cx = _sx * 0.1f;
    this->_cy = _sy * 0.1f;
    this->_px = this->_size.value() * this->_cloudPosition.x;
    this->_py = this->_size.value() * this->_cloudPosition.y;

    if (this->_horizontalAlignment == HorizontalAlignments::Left) { _px = -_px; _cx = -_cx; }
    else if (this->_horizontalAlignment == HorizontalAlignments::Center) { _px = 0.0f; _cy = _cy * 0.5f; }
    else if (this->_horizontalAlignment == HorizontalAlignments::Right) { }

    if (this->_verticalAlignment == VerticalAligments::Top) { _py = -_py; _cy = -_cy; }
    else if (this->_verticalAlignment == VerticalAligments::Middle) { _py = 0.0f; _cx = _cx * 0.5f; }
    else if (this->_verticalAlignment == VerticalAligments::Bottom) { }

    nvgBeginPath(vg);
    nvgRoundedRect(vg, _px - (_sx * 0.5f)+20, _py - (_sy * 0.5f)+10, _sx, _sy, _sx / 2.0f);
    nvgPathWinding(vg, NVG_HOLE);
    nvgFillColor(vg, Colors::ToNvgColor(glm::vec4(0.0f, 0.0f, 0.0f, 64.0f)));
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgMoveTo(vg, _px - _cx, _py + _cy);
    nvgLineTo(vg, 0, 0);
    nvgLineTo(vg, _px + _cx, _py - _cy);
    nvgStrokeColor(vg, Colors::ToNvgColor(this->borderColor()));
    nvgStrokeWidth(vg, 4.0f);
    nvgStroke(vg);

    nvgBeginPath(vg);
    nvgRoundedRect(vg, _px - (_sx * 0.5f), _py - (_sy * 0.5f), _sx, _sy, _sx / 2.0f);
    nvgStrokeColor(vg, Colors::ToNvgColor(this->borderColor()));
    nvgStrokeWidth(vg, 4.0f);
    nvgStroke(vg);

    nvgBeginPath(vg);
    nvgMoveTo(vg, 0, 0);
    nvgLineTo(vg, _px - _cx, _py + _cy);
    nvgLineTo(vg, _px + _cx, _py - _cy);
    nvgClosePath(vg);
    nvgFillColor(vg, Colors::ToNvgColor(this->color()));
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgRoundedRect(vg, _px - (_sx * 0.5f), _py - (_sy * 0.5f), _sx, _sy, _sx / 2.0f);
    nvgFillColor(vg, Colors::ToNvgColor(this->color()));
    nvgFill(vg);

    float fontSize = int(32.0f * (this->_size.value() / this->_size.targetValue()));
    if (fontSize >= 5 && fontSize <= 32)
    {
        this->_borderColor.a = 255 * (this->_size.value() / this->_size.targetValue());
        int lineCount = this->_lines.size();
        float y = -(lineCount / 2.0f) * fontSize;

        nvgFontSize(vg, fontSize);
        nvgFontFace(vg, this->fontFamily().c_str());
        nvgFillColor(vg, Colors::ToNvgColor(this->fontColor()));
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_TOP);
        for (auto line : this->_lines)
        {
            nvgText(vg, _px, _py + y, line.c_str(), NULL);
            y += fontSize;
        }
    }

    nvgRestore(vg);
}

void HintControl::setAlignment(HorizontalAlignments hor, VerticalAligments ver)
{
    this->_horizontalAlignment = hor;
    this->_verticalAlignment = ver;
}

void HintControl::setCloudPosition(const  glm::vec2& pos)
{
    this->_cloudPosition = pos;
}
void HintControl::addLines(const char* fmt, ...)
{
    va_list args;

    auto msg = new char[1000];

    va_start(args, fmt);
    vsprintf(msg, fmt, args);
    va_end(args);

    std::string lines(msg);
    auto found = lines.find('\n');
    while (found != std::string::npos)
    {
        this->_lines.push_back(lines.substr(0, found));
        lines = lines.substr(found + 1);
        found = lines.find('\n');
    }
    this->_lines.push_back(lines);
}

void HintControl::clearLines()
{
    this->_lines.clear();
}

void HintControl::setHideDelay(float delayInSeconds)
{
    Timer::Manager().addTimer(delayInSeconds, [this] () {
        this->_size.reverse().start();
        this->_state = 1;
    });
}

void HintControl::reset()
{
    this->_state = 0;
    this->clearLines();
    this->_size.from(0.1f).to(100.0f).in(0.2f).start();
}

const std::string& HintControl::id() const
{
    return Control::id();
}

bool HintControl::isDone()
{
    return this->_size.done() && this->_state >= 1;
}
