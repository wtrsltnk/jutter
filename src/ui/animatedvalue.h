#ifndef ANIMATEDVALUE_H
#define ANIMATEDVALUE_H

enum class AnimationStyles
{
    Linear,
    Logarithmic,
    EaseIn,
    EaseOut,
    Bounce,
};

class AnimatedValue
{
protected:
    float _beginValue;
    float _targetValue;
    float _currentValue;
    float _endTime;
    float _currentTime;
    bool _enabled;

public:
    AnimatedValue();
    virtual ~AnimatedValue();

    void update(float elapsed);
    const float& value() const;

    AnimatedValue& start();
    AnimatedValue& stop();
    AnimatedValue& resume();

    AnimatedValue& from(float beginValue);
    AnimatedValue& to(float targetValue);
    AnimatedValue& in(float time);

    AnimatedValue& reverse();

    bool done() const;
    float targetValue() const { return this->_targetValue; }
};

#endif // ANIMATEDVALUE_H
