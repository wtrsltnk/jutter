#include "ui.h"
#include "control.h"
#include "fadeoutlabelcontrol.h"
#include "fadeoutswipe.h"
#include "hintcontrol.h"
#include "colors.h"

#include "../system/input.h"
#include "../system/platform-opengl.h"
#include "../common/log.h"

#include "nanovg.h"
#ifdef __ANDROID__
#define NANOVG_GLES3
#elif _WIN32
#define NANOVG_GL3
#else
#define NANOVG_GL2
#endif
#include "nanovg_gl.h"
#include "font-icons.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>

glm::vec4 Colors::Primary = glm::vec4(57, 102, 46, 255);
glm::vec4 Colors::Secondary = glm::vec4(31, 79, 141, 255);
glm::vec4 Colors::Bright = glm::vec4(255, 255, 255, 255);
glm::vec4 Colors::Dark = glm::vec4(0, 45, 0, 255);
glm::vec4 Colors::Highlight = glm::vec4(161, 77, 49, 255);

NVGcolor Colors::ToNvgColor(const glm::vec4& color)
{
    return nvgRGBA(color.r, color.g, color.b, color.a);
}

#define ICON_SEARCH 0x1F50D
#define ICON_CIRCLED_CROSS 0x2716
#define ICON_CHEVRON_RIGHT 0xE75E
#define ICON_CHECK 0x2713
#define ICON_LOGIN 0xE740
#define ICON_TRASH 0xE729
#define ICON_RETRY 0x27F2

char* cpToUTF8(int cp, char* str)
{
    int n = 0;
    if (cp < 0x80) n = 1;
    else if (cp < 0x800) n = 2;
    else if (cp < 0x10000) n = 3;
    else if (cp < 0x200000) n = 4;
    else if (cp < 0x4000000) n = 5;
    else if (cp <= 0x7fffffff) n = 6;
    str[n] = '\0';
    switch (n) {
    case 6: str[5] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x4000000;
    case 5: str[4] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x200000;
    case 4: str[3] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x10000;
    case 3: str[2] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x800;
    case 2: str[1] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0xc0;
    case 1: str[0] = cp;
    }
    return str;
}

UI* UI::_instance = nullptr;

UI::UI()
    : _hoverControl(nullptr), _clickControl(nullptr)
{ }

UI& UI::Manager()
{
    if (UI::_instance == nullptr) UI::_instance = new UI();

    return *UI::_instance;
}

UI::~UI()
{ }

bool UI::init(const IInput* input)
{
    this->_input = input;
    this->_swipeHandle = this->_input->getAnalogActionHandle("throwing");
    this->_startSwipingHandle = this->_input->getDigitalActionHandle("start_throw");

#ifdef __ANDROID__
    this->vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#elif _WIN32
    this->vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#else
    this->vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#endif

    if (this->vg == nullptr)
    {
        Log::Current().Error("Could not create NanoVG context.");
        return false;
    }

    auto fontawesome = nvgCreateFont(this->vg, "fontawesome", "fontawesome-webfont.ttf");
    if (fontawesome == -1)
    {
        Log::Current().Error("Could not add fontawesome.");
        return false;
    }
    auto fontBold = nvgCreateFont(this->vg, "sans-bold", "Roboto-Bold.ttf");
    if (fontBold == -1)
    {
        Log::Current().Error("Could not add font bold.");
        return false;
    }
    auto collegiate = nvgCreateFont(this->vg, "collegiate", "FargoFaroNF.ttf");
    if (collegiate == -1)
    {
        Log::Current().Error("Could not add collegiate.");
        return false;
    }
    auto hashtag = nvgCreateFont(this->vg, "handwritten", "Action Comcs Black.ttf");
    if (hashtag == -1)
    {
        Log::Current().Error("Could not add handwritten.");
        return false;
    }

    return true;
}

float menuSlideSpeed = 3.0f;

void UI::update(float elapsed)
{
    if (this->_isChangingMode)
    {
        this->_changingModeState += (elapsed * menuSlideSpeed);
        if (this->_changingModeState > 1.0f)
        {
            this->_isChangingMode = false;
            this->_changingModeState = 1.0f;
        }
        return ;
    }

    for (auto control : this->_controls) if (control->visible()) control->update(elapsed);

    for (auto control : this->_tempControls) control->update(elapsed);

    if (this->_input->getDigitalActionData(this->_startSwipingHandle).state)
    {
        if (this->_clickControl != this->_hoverControl) this->_clickControl = this->_hoverControl;
    }

    if (!this->_input->getDigitalActionData(this->_startSwipingHandle).state)
    {
        if (this->_clickControl != nullptr)
        {
            this->_clickedControls.push(this->_clickControl);
            this->_clickControl = nullptr;
        }
    }
}

void UI::render(int width, int height, float scale)
{
    nvgBeginFrame(this->vg, width, height, float(width) / float(height));

    nvgSave(this->vg);

    if (this->_isChangingMode)
    {
        nvgSave(this->vg);
        nvgTranslate(this->vg, (width * this->_changingModeState), 0.0f);
        for (auto control : this->_prevControls) if (control->visible()) control->render(this->vg, scale);
        nvgRestore(this->vg);
        nvgTranslate(this->vg, -width + (width * this->_changingModeState), 0.0f);
    }

    for (auto control : this->_controls) if (control->visible()) control->render(this->vg, scale);

    for (auto control : this->_tempControls) if (!control->isDone()) control->render(this->vg, scale);

    nvgRestore(this->vg);

#ifndef __ANDROID__
    nvgSave(vg);

    nvgTranslate(vg, this->currentMousePos().x, this->currentMousePos().y);
    nvgScale(vg, scale, scale);
    char icon[8];
    nvgFontSize(vg, 48.0f);
    nvgFontFace(vg, "fontawesome");
    nvgFillColor(vg, Colors::ToNvgColor(Colors::Bright));
    nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
    if (this->_input->getDigitalActionData(this->_startSwipingHandle).state)
        nvgText(vg, 0.0f, 0.0f, cpToUTF8(int(eFontAwesomeIcons::FA_HAND_GRAB_O), icon), NULL);
    else
        nvgText(vg, 0.0f, 0.0f, cpToUTF8(int(eFontAwesomeIcons::FA_HAND_STOP_O), icon), NULL);

    nvgRestore(vg);
#endif // _WIN32

    nvgEndFrame(this->vg);
}

HintControl* UI::addHint()
{
    for (IFadableControl* c : this->_tempControls)
    {
        if (c->id() == "fade-out-hint" && c->isDone())
        {
            auto lbl = (HintControl*)c;
            lbl->reset();
            return lbl;
        }
    }

    auto control = new HintControl("fade-out-hint");
    control->setColor(glm::vec4(255, 255, 255, 255));
    control->reset();
    this->_tempControls.insert(control);
    return control;
}

FadeOutLabel* UI::addTempLabel()
{
    for (IFadableControl* c : this->_tempControls)
    {
        if (c->id() == "fade-out-label" && c->isDone())
        {
            auto lbl = (FadeOutLabel*)c;
            lbl->fadeOut().reset();
            return lbl;
        }
    }

    auto control = new FadeOutLabel("fade-out-label");
    control->setFontFamily("collegiate");
    control->setSize(glm::vec2(32.0f));
    control->setColor(glm::vec4(255, 255, 255, 255));
    control->fadeOut().reset();
    this->_tempControls.insert(control);
    return control;
}

FadeOutLabel* UI::addTempLabel(const std::string& text, const glm::vec2& pos)
{
    auto label = this->addTempLabel();
    label->fadeOut().setSpeed(50.0f);
    label->fadeOut().setFading(true);
    label->setText(text);
    label->setPosition(pos);
    label->setZoomOutEffect(false);
    return label;
}

FadeOutSwipe* UI::addTempSwipe()
{
    for (IFadableControl* c : this->_tempControls)
    {
        if (c->id() == "fade-out-swipe" && c->isDone())
        {
            auto c2 = (FadeOutSwipe*)c;
            c2->fadeOut().reset();
            return c2;
        }
    }

    auto control = new FadeOutSwipe("fade-out-swipe");
    control->setSize(glm::vec2(32.0f));
    control->setColor(glm::vec4(255, 255, 255, 255));
    control->fadeOut().reset();
    this->_tempControls.insert(control);
    return control;
}

void UI::addToGroup(GameModes mode, Control* control)
{
    if (this->_groups.find(mode) == this->_groups.end())
        this->_groups.insert(std::make_pair(mode, std::list<Control*>()));
    this->_groups[mode].insert(this->_groups[mode].end(), control);
}

void UI::removeFromGroup(GameModes mode, Control* control)
{
    if (this->_groups.find(mode) != this->_groups.end())
    {
        auto pos = std::find(this->_groups[mode].begin(), this->_groups[mode].end(), control);
        if (pos != this->_groups[mode].end()) this->_groups[mode].erase(pos);
    }
}

void UI::changeGameMode(GameModes mode)
{
    this->_prevControls = this->_controls;
    this->_isChangingMode = true;
    this->_changingModeState = 0.0f;

    if (this->_groups.find(mode) != this->_groups.end())
        this->_controls = this->_groups[mode];
    else
        this->_controls = std::list<Control*>();

    this->_clickControl = nullptr;
    while (!this->_clickedControls.empty()) this->_clickedControls.pop();
    this->_hoverControl = nullptr;
}

void UI::setHoverControl(Control* control)
{
    this->_hoverControl = control;
}

const Control* UI::hoverControl() const
{
    return this->_hoverControl;
}

std::queue<Control*>& UI::clickedControls()
{
    return this->_clickedControls;
}

glm::vec2 UI::currentMousePos()
{
    auto data = this->_input->getAnalogActionData(this->_swipeHandle);
    return glm::vec2(data.x, data.y);
}
