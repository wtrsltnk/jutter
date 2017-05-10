#ifndef FADEOUT_H
#define FADEOUT_H

class FadeOut
{
    bool _fading;
    float _value;
    float _speed;
public:
    FadeOut();
    virtual ~FadeOut();

    virtual void update(float elapsed);
    virtual bool canBeDeleted() const;

    void reset();
    bool isFading() const;
    void setFading(bool fading);
    bool isFaded() const;
    float value() const;

    float speed() const;
    void setSpeed(float speed);
};

#endif // FADEOUTCONTROL_H
