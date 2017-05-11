#include "gamemode.h"
#include "../ui/ui.h"
#include "../ui/fadeoutswipe.h"
#include "../gamerules.h"
#include "../entities/entitymanager.h"

GameMode::GameMode(class GameRules* gameRules)
    : _gameRules(gameRules), gameRulesTime(0.0f)
{ }

GameMode::~GameMode() { }

void GameMode::onExitFrom() { }

void GameMode::addToUI(class Control* control)
{
    UI::Manager().addToGroup(this->gameMode(), control);
}

bool GameMode::update(float elapsed)
{
    gameRulesTime += elapsed;

    return true;
}
