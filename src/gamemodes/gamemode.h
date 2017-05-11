#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "gamemodes.h"

#include <vector>
#include <glm/glm.hpp>

extern float screenScale;

class GameMode
{
    float gameRulesTime;

protected:
    class GameRules* _gameRules;

public:
    GameMode(class GameRules* gameRules);
	virtual ~GameMode();
    virtual void setup(int width, int height) = 0;
    virtual void resize(int width, int height) = 0;
    virtual void onExitFrom();
    virtual void onSwitchTo() = 0;
    virtual bool handleClick(class Control* control) = 0;
    virtual GameModes gameMode() const = 0;

    virtual bool update(float elapsed);

    void addToUI(class Control* control);
};

#endif // GAMEMODE_H
