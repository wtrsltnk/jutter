#ifndef FADEOUTLABELCONTROL_H
#define FADEOUTLABELCONTROL_H

#include "labelcontrol.h"
#include "fadeablecontrol.h"

class FadeOutLabel : public Label, public IFadableControl
{
    FadeOut _fadeOut;
    bool _zoomOutEffect;
public:
    FadeOutLabel(const std::string& id);
    virtual ~FadeOutLabel();

    virtual const std::string& id() const;

    virtual void render(NVGcontext* vg, float scale = 1.0f);
    virtual void update(float elapsed);
    virtual bool isDone();

    virtual FadeOut& fadeOut();

    bool zoomOutEffect() const;
    void setZoomOutEffect(bool enable);
};

#endif // FADEOUTLABELCONTROL_H
