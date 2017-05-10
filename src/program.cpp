
#include "system/platform-opengl.h"
#include "system/sdl2-setup.h"
#include "system/input.h"

#include "entities/entitymanager.h"
#include "ui/ui.h"
#include "gamerules.h"
#include "common/postprocesseffect.h"
#include "common/log.h"
#include "common/particles.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

static const int BASELINE_WIDTH = 1776/2;
static const int BASELINE_HEIGHT = 1080/2;
float screenScale = 1.0f;

class Program : public SDLProgram
{
public:
    Program(int width, int height) : SDLProgram(width, height) { }

    virtual bool SetUp();
    virtual void Render();
    virtual void CleanUp();
    virtual void OnResize(int width, int height);

    glm::mat4 proj;

    GameRules _gameRules;

    PostProcessEffect _effects;
};

bool Program::SetUp()
{
    Log::Current().Verbose("bool Program::SetUp()");

    glEnable(GL_DEPTH_TEST);
    glClearColor((163.0f / 255.0f), (204.0f / 255.0f), (255.0f / 255.0f), 1.0f);

    Entity::Manager().init();
    Entity::Manager().reset();

    this->_gameRules.init(this->input(), this->width, this->height);

    this->_effects.setup(this->width, this->height);

    return true;
}

static auto lastTime = 0.0f;

void Program::Render()
{
    auto elapsed = this->elapsed();
    auto diff = elapsed - lastTime;
    lastTime = elapsed;

    UI::Manager().update(diff);

    if (!this->_gameRules.handleClickedButtons())
    {
        this->keepRunning = false;
        return;
    }

    this->_gameRules.update(diff);
    Entity::Manager().update(diff);
    Particles::Manager().Update(diff);

    glViewport(0, 0, this->width, this->height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    Entity::Manager().render(this->proj);

    Particles::Manager().Render(this->proj, Entity::Manager()._camera->getCameraMatrix());

    UI::Manager().render(this->width, this->height, screenScale);
}

void Program::OnResize(int width, int height)
{
    screenScale = width / float(BASELINE_WIDTH);
    glViewport(0, 0, width, height);

    if (Entity::Manager()._camera != nullptr) Entity::Manager()._camera->setViewport(glm::vec4(0, 0, width, height));
    this->proj = glm::perspective(glm::radians(60.0f), float(this->width) / float(this->height), 0.1f, 4096.0f);
}

void Program::CleanUp()
{
    this->_effects.cleanup();
}

int main(int argc, char* argv[])
{
    return Program(BASELINE_WIDTH, BASELINE_HEIGHT/*1440, 960*/).Run(argc, argv);
}
