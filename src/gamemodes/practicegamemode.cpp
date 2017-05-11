#include "practicegamemode.h"
#include "../ui/ui.h"
#include "../ui/buttoncontrol.h"
#include "../ui/scorebugcontrol.h"
#include "../ui/fadeoutlabelcontrol.h"
#include "../ui/hintcontrol.h"
#include "../entities/entitymanager.h"
#include "../entities/worldentity.h"
#include "../gamerules.h"
#include "../common/particles.h"
#include "../common/timer.h"
#include <sstream>

#define HINT_TIMEOUT 10.0f

PracticeGameMode::PracticeGameMode(class GameRules* gameRules)
    : GameMode(gameRules), _back(nullptr), _isPanning(false)
{
    this->reset();
    this->_randm.setSeed(6346);
}

PracticeGameMode::~PracticeGameMode() { }

void PracticeGameMode::setup(int width, int height)
{
    this->_back = new Button("backPlay");
    this->_back->setIcon(eFontAwesomeIcons::FA_CHEVRON_CIRCLE_LEFT);
    this->_back->setText("back");
    this->addToUI(this->_back);

    this->resize(width, height);
}

void PracticeGameMode::resize(int width, int height)
{
    this->_width = width;
    this->_height = height;
    if (this->_back == nullptr) return;

    this->_back->setPosition(glm::vec2(OFFSET_ONE_BUTTON, height - OFFSET_ONE_BUTTON));
}

void PracticeGameMode::onExitFrom()
{ }

void PracticeGameMode::onSwitchTo()
{
    Entity::Manager().moveToTopView();
}

bool PracticeGameMode::handleClick(Control* control)
{
    if (control == this->_back)
    {
        this->_gameRules->changeGameMode(GameModes::MainMenu);
    }

    return true;
}

void PracticeGameMode::handleInput()
{
    auto pos = this->_gameRules->getPanningData();
    if (this->_isPanning)
    {
        if (!this->_gameRules->getPanningState())
        {
            this->_isPanning = false;
        }
        else
        {
            auto diff = pos - this->_prevDragPosition;
            auto camPos = Entity::Manager()._camera->_position;
            camPos.x += diff.x;
            camPos.y -= diff.y;
            Entity::Manager()._camera->_position = camPos;
            this->_prevDragPosition = pos;
        }
    }
    else
    {
        if (this->_gameRules->getPanningState())
        {
            this->_isPanning = true;
            this->_prevDragPosition = pos;
        }
    }

    auto zoom = this->_gameRules->getZoomingData();
    if (glm::length(zoom) > 0.0f)
    {
        auto camPos = Entity::Manager()._camera->_position;
        camPos.z += (zoom.y * 10.0f);
        Entity::Manager()._camera->_position = camPos;
    }
}

bool PracticeGameMode::update(float elapsed)
{
    if (!GameMode::update(elapsed)) return false;

    this->handleInput();

    return true;
}

void PracticeGameMode::reset()
{ }
