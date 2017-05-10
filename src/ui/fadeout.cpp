#include "fadeout.h"
#include <glm/glm.hpp>

FadeOut::FadeOut()
    : _fading(false), _value(255.0f), _speed(100.0f)
{ }

FadeOut::~FadeOut()
{ }

void FadeOut::update(float elapsed)
{
    if (this->isFading())
    {
        this->_value -= (this->_speed * elapsed);
        this->setFading(this->_value > 0.0f);
    }
}

bool FadeOut::canBeDeleted() const
{
    return this->isFaded();
}

void FadeOut::reset()
{
    this->_value = 255.0f;
    this->setFading(true);
}

bool FadeOut::isFading() const
{
    return this->_fading;
}

void FadeOut::setFading(bool fading)
{
    this->_fading = fading;
}

bool FadeOut::isFaded() const
{
    return this->_value < 0.0f;
}

float FadeOut::value() const
{
    return this->_value;
}

float FadeOut::speed() const
{
    return this->_speed;
}

void FadeOut::setSpeed(float speed)
{
    this->_speed = speed;
}
