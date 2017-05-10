#ifndef CONFIRMEXITGAMEMODE_H
#define CONFIRMEXITGAMEMODE_H

#include "gamemode.h"

class ConfirmExitGameMode : public GameMode
{
    class Panel* _confirmExitPanel;
    class Label* _confirmExitLabel;
    class Button* _confirmExitYes;
    class Button* _confirmExitNo;

public:
    ConfirmExitGameMode(class GameRules* gameRules);
    virtual ~ConfirmExitGameMode();

    virtual void setup(int width, int height);
    virtual void resize(int width, int height);
    virtual void onSwitchTo();
    virtual bool handleClick(class Control* control);
    virtual GameModes gameMode() const { return GameModes::ConfirmExit; }
};


#endif // CONFIRMEXITGAMEMODE_H
