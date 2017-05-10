#ifndef GAMERULES_H
#define GAMERULES_H

#include "system/iinput.h"
#include "entities/entity.h"
#include "entities/cameraentity.h"
#include "gamemodes/gamemodes.h"
#include "gamemodes/gamemode.h"
#include "gamemodes/mainmenumode.h"
#include "gamemodes/confirmexitgamemode.h"
#include "gamemodes/practicegamemode.h"

#include <vector>
#include <set>
#include <glm/glm.hpp>

class GameRules
{
    const IInput* _input;
    AnalogActionHandle _swipeHandle;
    DigitalActionHandle _startSwipingHandle;

    MainMenuMode _mainMenuMode;
    ConfirmExitGameMode _confirmExitMode;
    PracticeGameMode _practiceMode;

    GameModes _prevGameMode;
    GameModes _gameMode;
    GameMode* _gameModeRules;

public:
    GameRules();
    virtual ~GameRules();

    void init(const IInput* input, int width, int height);
    void resize(int width, int height);
    bool update(float elapsed);

    const glm::vec2 getSwipeData();
    bool getSwipeState();

    GameModes gameMode() const;

    // Button actions
    bool handleClickedButtons();
    void changeGameMode(GameModes newMode);
    void returnToPreviousGameMode();
    void practiceLevel();
};

#endif // GAMERULES_H
