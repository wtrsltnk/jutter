#ifndef UI_H
#define UI_H

#include <map>
#include <list>
#include <set>
#include <queue>
#include <string>
#include <glm/glm.hpp>
#include "../gamemodes/gamemodes.h"
#include "../system/iinput.h"
#include "fadeablecontrol.h"

#include "nanovg.h"

class UI
{
    const IInput* _input;
    AnalogActionHandle _swipeHandle;
    DigitalActionHandle _startSwipingHandle;

    std::set<IFadableControl*> _tempControls;
    std::map<GameModes, std::list<class Control*> > _groups;
    std::list<class Control*> _controls;
    std::list<class Control*> _prevControls;
    class Control* _hoverControl;
    class Control* _clickControl;
    std::queue<class Control*> _clickedControls;

    bool _isChangingMode;
    float _changingModeState;

    NVGcontext* vg;

    static UI* _instance;
    UI();
public:
    static UI& Manager();
    virtual ~UI();

    bool init(const IInput* input);
    virtual void update(float elapsed);
    virtual void render(int width, int height, float scale = 1.0f);

    class HintControl* addHint();
    class FadeOutLabel* addTempLabel();
    class FadeOutLabel* addTempLabel(const std::string& text, const glm::vec2& pos);
    class FadeOutSwipe* addTempSwipe();

    void addToGroup(GameModes mode, class Control* control);
    void removeFromGroup(GameModes mode, class Control* control);
    void changeGameMode(GameModes mode);

    void setHoverControl(class Control* control);
    const class Control* hoverControl() const;
    std::queue<class Control*>& clickedControls();

    glm::vec2 currentMousePos();
};

#endif // UI_H
