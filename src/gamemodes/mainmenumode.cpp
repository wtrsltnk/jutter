#include "mainmenumode.h"
#include "../ui/imagecontrol.h"
#include "../ui/buttoncontrol.h"
#include "../gamerules.h"
#include "../entities/entitymanager.h"

MainMenuMode::MainMenuMode(class GameRules* gameRules)
    : GameMode(gameRules), _startPlay(nullptr), _exitToMenu(nullptr)
{ }

MainMenuMode::~MainMenuMode() { }

void MainMenuMode::setup(int width, int height)
{
    this->_startPlay = new Button("startPlay");
    this->_startPlay->setIcon(eFontAwesomeIcons::FA_PLAY);
    this->_startPlay->setText("");
    this->_startPlay->setSize(glm::vec2(96.0f));
    this->addToUI(this->_startPlay);

    this->_exitToMenu = new Button("exitToMenu");
    this->_exitToMenu->setIcon(eFontAwesomeIcons::FA_SIGN_OUT);
    this->_exitToMenu->setText("exit");
    this->addToUI(this->_exitToMenu);

    this->resize(width, height);
}

void MainMenuMode::resize(int width, int height)
{
    this->_startPlay->setPosition(glm::vec2(width / 2.0f, height / 2.0f));
    this->_exitToMenu->setPosition(glm::vec2(OFFSET_ONE_BUTTON, height - OFFSET_ONE_BUTTON));
}

void MainMenuMode::onSwitchTo()
{
    Entity::Manager().moveToTopView();
}

bool MainMenuMode::handleClick(Control* control)
{
    if (control == this->_startPlay)
    {
        this->_gameRules->changeGameMode(GameModes::Practice);
    }
    else if (control == this->_exitToMenu)
    {
        this->_gameRules->changeGameMode(GameModes::ConfirmExit);
    }

    return true;
}
