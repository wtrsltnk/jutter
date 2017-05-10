#include "confirmexitgamemode.h"
#include "../ui/panelcontrol.h"
#include "../ui/labelcontrol.h"
#include "../ui/buttoncontrol.h"
#include "../gamerules.h"
#include "../entities/entitymanager.h"

ConfirmExitGameMode::ConfirmExitGameMode(class GameRules* gameRules)
    : GameMode(gameRules), _confirmExitPanel(nullptr), _confirmExitLabel(nullptr),
      _confirmExitYes(nullptr), _confirmExitNo(nullptr)
{ }

ConfirmExitGameMode::~ConfirmExitGameMode()
{ }

void ConfirmExitGameMode::setup(int width, int height)
{
    this->_confirmExitPanel = new Panel("confirmExitPanel");
    this->addToUI(this->_confirmExitPanel);

    this->_confirmExitLabel = new Label("confirmExitLabel");
    this->_confirmExitLabel->setText("Really Exit?");
    this->_confirmExitLabel->setFontFamily("sans-bold");
    this->_confirmExitLabel->setSize(glm::vec2(48.0f));
    this->addToUI(this->_confirmExitLabel);

    this->_confirmExitYes = new Button("confirmExitYes");
    this->_confirmExitYes->setIcon(eFontAwesomeIcons::FA_CHECK);
    this->_confirmExitYes->setText("yes");
    this->addToUI(this->_confirmExitYes);

    this->_confirmExitNo = new Button("confirmExitNo");
    this->_confirmExitNo->setIcon(eFontAwesomeIcons::FA_TIMES);
    this->_confirmExitNo->setText("no");
    this->addToUI(this->_confirmExitNo);

    this->resize(width, height);
}

void ConfirmExitGameMode::resize(int width, int height)
{
    this->_confirmExitPanel->setPosition(glm::vec2(width / 2.0f, height / 2.0f));
    this->_confirmExitPanel->setSize(glm::vec2(400.0f, 250.0f));
    this->_confirmExitLabel->setPosition(glm::vec2(width / 2.0f, height / 2.0f - OFFSET_ONE_BUTTON));
    this->_confirmExitYes->setPosition(glm::vec2(width / 2.0f - OFFSET_TWO_BUTTONS, height / 2.0f + OFFSET_ONE_BUTTON));
    this->_confirmExitNo->setPosition(glm::vec2(width / 2.0f + OFFSET_TWO_BUTTONS, height / 2.0f + OFFSET_ONE_BUTTON));
}

void ConfirmExitGameMode::onSwitchTo()
{
    Entity::Manager().moveToTopView();
}

bool ConfirmExitGameMode::handleClick(Control* control)
{
    if (control == this->_confirmExitYes)
    {
        return false;
    }
    else if (control == this->_confirmExitNo)
    {
        this->_gameRules->returnToPreviousGameMode();
    }

    return true;
}
