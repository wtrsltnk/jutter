#include "fadeoutswipe.h"
#include "colors.h"
#include "fonts.h"

FadeOutSwipe::FadeOutSwipe(const std::string& id)
    : Control(id)
{ }

FadeOutSwipe::~FadeOutSwipe() { }

const std::string& FadeOutSwipe::id() const
{
    return Control::id();
}

void FadeOutSwipe::render(NVGcontext* vg, float scale)
{
    this->_color.a = this->_fadeOut.value();

    nvgSave(vg);

    nvgBeginPath(vg);
    nvgMoveTo(vg, this->_swipe[0].x, this->_swipe[0].y);
    for (int i = 1; i < this->_swipe.size(); i++)
        nvgLineTo(vg, this->_swipe[i].x, this->_swipe[i].y);
    nvgStrokeColor(vg, Colors::ToNvgColor(this->color()));
    nvgStrokeWidth(vg, this->_speed / 5.0f);
    nvgStroke(vg);

    nvgTranslate(vg, this->_swipe.front().x, this->_swipe.front().y);

    nvgScale(vg, scale * this->_scale, scale * this->_scale);

    char icon[8];
    nvgFontSize(vg, (this->size().x * 0.5f));
    nvgFontFace(vg, "fontawesome");
    nvgFillColor(vg, Colors::ToNvgColor(this->color()));
    nvgTextAlign(vg,NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgText(vg, 0.0f, 0.0f, cpToUTF8(int(eFontAwesomeIcons::FA_CIRCLE), icon), NULL);

    nvgRestore(vg);

    nvgSave(vg);

    nvgTranslate(vg, this->_swipe.back().x, this->_swipe.back().y);

    nvgScale(vg, scale * this->_scale, scale * this->_scale);

    nvgFontSize(vg, (this->size().x * 0.5f));
    nvgFontFace(vg, "fontawesome");
    nvgFillColor(vg, Colors::ToNvgColor(this->color()));
    nvgTextAlign(vg,NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    nvgText(vg, 0.0f, 0.0f, cpToUTF8(int(eFontAwesomeIcons::FA_CIRCLE), icon), NULL);

    nvgRestore(vg);
}

void FadeOutSwipe::update(float elapsed)
{
    this->_fadeOut.update(elapsed);
}

bool FadeOutSwipe::isDone()
{
    return this->fadeOut().isFaded();
}

void FadeOutSwipe::setSwipe(const std::vector<glm::vec2>& swipe, float speed)
{
    this->_swipe = swipe;
    this->_speed = speed;
}

FadeOut& FadeOutSwipe::fadeOut()
{
    return this->_fadeOut;
}
