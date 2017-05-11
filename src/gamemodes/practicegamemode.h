#ifndef PRACTICEGAMEMODE_H
#define PRACTICEGAMEMODE_H

#include "gamemode.h"
#include "../common/randm.h"
#include <glm/glm.hpp>

class PracticeGameMode : public GameMode
{
    class Button* _back;
    RandomNumberGenerator _randm;
    int _width, _height;
public:
    PracticeGameMode(class GameRules* gameRules);
    virtual ~PracticeGameMode();

	virtual void setup(int width, int height);
    virtual void resize(int width, int height);
    virtual void onExitFrom();
    virtual void onSwitchTo();
    virtual bool handleClick(class Control* control);
    virtual void handleInput();
    virtual GameModes gameMode() const { return GameModes::Practice; }
    virtual bool update(float elapsed);

    void reset();

    bool _isPanning;
    glm::vec2 _prevDragPosition;
};

#endif // PRACTICEGAMEMODE_H
