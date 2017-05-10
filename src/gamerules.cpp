#include "gamerules.h"
#include "entities/entitymanager.h"
#include "entities/entity.h"
#include "system/input.h"
#include "ui/ui.h"
#include "ui/fadeoutlabelcontrol.h"
#include "ui/fadeoutswipe.h"
#include "common/particles.h"
#include "common/timer.h"

#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

GameRules::GameRules()
    : _input(nullptr), _prevGameMode(GameModes::MainMenu), _gameMode(GameModes::Practice),
      _mainMenuMode(this), _confirmExitMode(this),
      _practiceMode(this), _gameModeRules(nullptr)
{ }

GameRules::~GameRules()
{ }

void GameRules::init(const IInput* input, int width, int height)
{
    UI::Manager().init(input);
    this->_input = input;
    this->_swipeHandle = this->_input->getAnalogActionHandle("throwing");
    this->_startSwipingHandle = this->_input->getDigitalActionHandle("start_throw");

    this->_mainMenuMode.setup(width, height);
    this->_confirmExitMode.setup(width, height);
    this->_practiceMode.setup(width, height);

    Entity::Manager().moveToDefaultView();

    this->changeGameMode(this->_gameMode);
}

void GameRules::resize(int width, int height)
{
    this->_mainMenuMode.resize(width, height);
    this->_confirmExitMode.resize(width, height);
    this->_practiceMode.resize(width, height);
}

bool GameRules::handleClickedButtons()
{
    if (!UI::Manager().clickedControls().empty())
    {
        auto control = UI::Manager().clickedControls().back();
        UI::Manager().clickedControls().pop();

        if (this->_gameModeRules != nullptr) return this->_gameModeRules->handleClick(control);
    }

    return true;
}

void GameRules::changeGameMode(GameModes newMode)
{
    this->_prevGameMode = this->_gameMode;
    this->_gameMode = newMode;
    UI::Manager().changeGameMode(this->_gameMode);

    if (this->_gameModeRules != nullptr) this->_gameModeRules->onExitFrom();

    switch (this->gameMode())
    {
    case GameModes::ConfirmExit: { this->_gameModeRules = &this->_confirmExitMode; break; }
    case GameModes::MainMenu:    { this->_gameModeRules = &this->_mainMenuMode; break; }
    case GameModes::Practice:    { this->_gameModeRules = &this->_practiceMode; break; }
    }

    if (this->_gameModeRules != nullptr) this->_gameModeRules->onSwitchTo();
}

bool GameRules::update(float elapsed)
{
    Timer::Manager().update(elapsed);

    if (this->_gameModeRules != nullptr) return this->_gameModeRules->update(elapsed);

    return true;
}

const glm::vec2 GameRules::getSwipeData()
{
    return glm::vec2(
                this->_input->getAnalogActionData(this->_swipeHandle).x,
                this->_input->getAnalogActionData(this->_swipeHandle).y
                );
}

bool GameRules::getSwipeState()
{
    return this->_input->getDigitalActionData(this->_startSwipingHandle).state;
}

void GameRules::returnToPreviousGameMode()
{
    this->changeGameMode(this->_prevGameMode);
}

void GameRules::practiceLevel()
{
    this->_practiceMode.reset();
    Entity::Manager().moveToDefaultView();
    this->changeGameMode(GameModes::Practice);
}

GameModes GameRules::gameMode() const
{
    return this->_gameMode;
}
