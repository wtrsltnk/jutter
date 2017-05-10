#ifndef HINTCONTROL_H
#define HINTCONTROL_H

#include "control.h"
#include "animatedvalue.h"
#include "fadeablecontrol.h"

#include <vector>
#include <cstdarg>

class HintBalloon
{
public:
    AnimatedValue _sizex, _sizey;
    AnimatedValue _posx, _posy;

    inline void update(float elapsed) { _sizex.update(elapsed); _sizey.update(elapsed); _posx.update(elapsed); _posy.update(elapsed); }
    inline void reset()
    {
        _sizex.stop().start();
        _sizey.stop().start();
        _posx.stop().start();
        _posy.stop().start();
    }
};

enum class HorizontalAlignments
{
    Left,
    Center,
    Right
};

enum class VerticalAligments
{
    Top,
    Middle,
    Bottom
};

class HintControl : public Control, public IFadableControl
{
    float _sx;
    float _sy;
    float _cx;
    float _cy;
    float _px;
    float _py;
    int _state;
    AnimatedValue _size;
    HorizontalAlignments _horizontalAlignment;
    VerticalAligments _verticalAlignment;
    glm::vec2 _cloudPosition;
    std::vector<std::string> _lines;
public:
    HintControl(const std::string& id);
    virtual ~HintControl();

    virtual const std::string& id() const;

    virtual void update(float elapsed);
    virtual void render(NVGcontext* vg, float scale = 1.0f);
    virtual bool isDone();

    void setAlignment(HorizontalAlignments hor, VerticalAligments ver);
    void setCloudPosition(const glm::vec2& pos);
    void addLines(const char* fmt, ...);
    void clearLines();
    void setHideDelay(float delayInSeconds);
    void reset();


};

#endif // HINTCONTROL_H
