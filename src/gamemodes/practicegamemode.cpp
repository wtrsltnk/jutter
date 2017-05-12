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

    this->_zoomIncrease = new Button("zoomIncrease");
    this->_zoomIncrease->setIcon(eFontAwesomeIcons::FA_PLUS_CIRCLE);
    this->_zoomIncrease->setText("zoom-in");
    this->addToUI(this->_zoomIncrease);

    this->_zoomDecrease = new Button("zoomDecrease");
    this->_zoomDecrease->setIcon(eFontAwesomeIcons::FA_MINUS_CIRCLE);
    this->_zoomDecrease->setText("zoom-out");
    this->addToUI(this->_zoomDecrease);

    this->resize(width, height);
}

void PracticeGameMode::resize(int width, int height)
{
    this->_width = width;
    this->_height = height;
    if (this->_back == nullptr) return;

    this->_back->setPosition(glm::vec2(OFFSET_ONE_BUTTON, height - OFFSET_ONE_BUTTON));
    this->_zoomIncrease->setPosition(glm::vec2(width - OFFSET_ONE_BUTTON, height - OFFSET_ONE_BUTTON));
    this->_zoomDecrease->setPosition(glm::vec2(width - OFFSET_ONE_BUTTON, height - OFFSET_TWO_BUTTONS));
}

void PracticeGameMode::onExitFrom()
{ }

void PracticeGameMode::onSwitchTo()
{
    Entity::Manager().moveToTopView();
    auto randomPos = WorldEntity::RandomPointOnBeach();
}

bool PracticeGameMode::handleClick(Control* control)
{
    if (control == this->_back)
    {
        this->_gameRules->changeGameMode(GameModes::MainMenu);
    }
    else if (control == this->_zoomIncrease)
    {
        Entity::Manager()._camera->zoom(50.0f);
    }
    else if (control == this->_zoomDecrease)
    {
        Entity::Manager()._camera->zoom(-50.0f);
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
        Entity::Manager()._camera->zoom(zoom.y * 10.0f);
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
