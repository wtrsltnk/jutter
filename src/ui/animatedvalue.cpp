#include "animatedvalue.h"

AnimatedValue::AnimatedValue()
    : _currentValue(0.0f), _beginValue(0.0f), _targetValue(0.0f),
    _currentTime(0.0f), _endTime(0.0f), _enabled(false)
{ }

AnimatedValue::~AnimatedValue() { }

void AnimatedValue::update(float elapsed)
{
    // Are we done animating?
    if (!this->_enabled) return;

    this->_currentTime += elapsed;
    if (this->_currentTime > this->_endTime)
    {
        this->_currentTime = this->_endTime;
        this->_currentValue = this->_targetValue;

        // We stop animation
        this->stop();
    }
    else
    {
        auto dt= (1.0f / this->_endTime) * this->_currentTime;
        this->_currentValue = this->_beginValue + ((this->_targetValue - this->_beginValue) * dt);
    }
}

const float& AnimatedValue::value() const { return this->_currentValue; }

AnimatedValue& AnimatedValue::start()
{
    this->_enabled = true;
    this->_currentValue = this->_beginValue;
    this->_currentTime = 0.0f;

    return *this;
}

AnimatedValue& AnimatedValue::stop()
{
    this->_enabled = false;

    return *this;
}

AnimatedValue& AnimatedValue::resume()
{
    this->_enabled = true;

    return *this;
}

AnimatedValue& AnimatedValue::from(float beginValue) { this->_beginValue = beginValue; return *this; }

AnimatedValue& AnimatedValue::to(float targetValue) { this->_targetValue = targetValue; return *this; }

AnimatedValue& AnimatedValue::in(float time) { this->_endTime = time; return *this; }

AnimatedValue& AnimatedValue::reverse()
{
    auto tmp = this->_beginValue;
    this->_beginValue = this->_targetValue;
    this->_targetValue = tmp;
    if (this->_enabled) this->start();
    else this->start().stop();

    return *this;
}

bool AnimatedValue::done() const
{
    return (this->_currentTime >= this->_endTime);
}
