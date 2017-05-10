#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "gamemodes.h"

#include <vector>
#include <glm/glm.hpp>

extern float screenScale;

enum class ThrowingStates
{
    Idle,
    Throw,
    Skip
};

class GameMode
{
    float gamerules_time;

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

    ThrowingStates _throwingState;
    std::vector<glm::vec2> _throwingPos;
    virtual void handleInput();
    virtual bool update(float elapsed);
    virtual void handleSwipe();
    virtual void handleTap(const glm::vec2& pos);

    void addToUI(class Control* control);
};

#endif // GAMEMODE_H
