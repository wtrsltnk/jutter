#ifndef FADEOUTSWIPE_H
#define FADEOUTSWIPE_H

#include "control.h"
#include "fadeablecontrol.h"

#include <vector>

class FadeOutSwipe : public Control, public IFadableControl
{
    FadeOut _fadeOut;
    std::vector<glm::vec2> _swipe;
    float _speed;
public:
    FadeOutSwipe(const std::string& id);
    virtual ~FadeOutSwipe();

    virtual const std::string& id() const;

    virtual void render(NVGcontext* vg, float scale = 1.0f);
    virtual void update(float elapsed);
    virtual bool isDone();

    void setSwipe(const std::vector<glm::vec2>& swipe, float speed);

    virtual FadeOut& fadeOut();
};

#endif // FADEOUTSWIPE_H
