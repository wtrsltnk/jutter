#include "gamemode.h"
#include "../ui/ui.h"
#include "../ui/fadeoutswipe.h"
#include "../gamerules.h"
#include "../entities/entitymanager.h"

GameMode::GameMode(class GameRules* gameRules)
    : _gameRules(gameRules), _throwingState(ThrowingStates::Idle),
      gamerules_time(0.0f)
{ }

GameMode::~GameMode() { }

void GameMode::onExitFrom() { }

void GameMode::addToUI(class Control* control)
{
    UI::Manager().addToGroup(this->gameMode(), control);
}

bool GameMode::update(float elapsed)
{
    gamerules_time += elapsed;

    return true;
}

float totalLength(const std::vector<glm::vec2>& pos)
{
    if (pos.size() <= 0) return 0.0f;
    float total = 0.0f;
    auto prev = pos.front();
    for (auto v : pos)
    {
        total += glm::length(v - prev);
        prev = v;
    }
    return total;
}

float averageLength(const std::vector<glm::vec2>& pos)
{
    if (pos.size() <= 0) return 0.0f;

    return totalLength(pos) / pos.size();
}

void GameMode::handleInput()
{
    auto swipe = this->_gameRules->getSwipeData();
    glm::vec2 pos(swipe.x, swipe.y);

    while (gamerules_time >= (1.0f / 30.0f))
    {
        gamerules_time -= (1.0f / 30.0f);
        switch (this->_throwingState)
        {
        case ThrowingStates::Idle:
        {
            if (this->_gameRules->getSwipeState())
            {
                if (UI::Manager().hoverControl() != nullptr)
                {
                    this->_throwingState = ThrowingStates::Skip;
                }
                else
                {
                    this->_throwingState = ThrowingStates::Throw;
                    this->_throwingPos.clear();
                }
            }
            break;
        }
        case ThrowingStates::Throw:
        {
            if (!this->_gameRules->getSwipeState())
            {
                this->_throwingState = ThrowingStates::Idle;

                // do something with the collected data
                if (this->_throwingPos.size() >= 2 && glm::length(this->_throwingPos.front() - this->_throwingPos.back()) > 0.001f)
                {
                    this->handleSwipe();
                }
                else
                {
                    this->handleTap(this->_throwingPos.back());
                }
            }

            if (this->_throwingPos.empty() || glm::length(pos - this->_throwingPos.back()) > 0)
            {
                this->_throwingPos.push_back(pos);
            }
            break;
        }

        case ThrowingStates::Skip:
        {
            if (!this->_gameRules->getSwipeState())
            {
                this->_throwingState = ThrowingStates::Idle;
            }
        }
        }
    }
}

void GameMode::handleSwipe()
{ }

void GameMode::handleTap(const glm::vec2& pos)
{ }
