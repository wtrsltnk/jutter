#include "fadeoutlabelcontrol.h"

FadeOutLabel::FadeOutLabel(const std::string &id)
    : Label(id), _zoomOutEffect(true)
{ }

FadeOutLabel::~FadeOutLabel()
{ }

const std::string& FadeOutLabel::id() const
{
    return Label::id();
}

void FadeOutLabel::render(NVGcontext* vg, float scale)
{
    this->_fontColor.a = this->_fadeOut.value();
    Label::render(vg, scale + (this->_zoomOutEffect ? (1.0f - (this->_fadeOut.value() / 255.0f)) : 0.0f));
}

void FadeOutLabel::update(float elapsed)
{
    this->_fadeOut.update(elapsed);
}

bool FadeOutLabel::isDone()
{
    return this->fadeOut().isFaded();
}

FadeOut& FadeOutLabel::fadeOut()
{
    return this->_fadeOut;
}

bool FadeOutLabel::zoomOutEffect() const
{
    return this->_zoomOutEffect;
}

void FadeOutLabel::setZoomOutEffect(bool enable)
{
    this->_zoomOutEffect = enable;
}
