#ifndef MAINMENUMODE_H
#define MAINMENUMODE_H

#include "gamemode.h"

class MainMenuMode : public GameMode
{
    class Button* _startPlay;
    class Button* _exitToMenu;
public:
    MainMenuMode(class GameRules* gameRules);
    virtual ~MainMenuMode();

    virtual void setup(int width, int height);
    virtual void resize(int width, int height);
    virtual void onSwitchTo();
    virtual bool handleClick(class Control* control);
    virtual GameModes gameMode() const { return GameModes::MainMenu; }
};

#endif // MAINMENUMODE_H
