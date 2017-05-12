#include "entitymanager.h"
#include "worldentity.h"
#include "../common/geometry.h"
#include "../common/randm.h"
#include "../common/particles.h"

#include <glm/gtc/matrix_transform.hpp>
#include <sstream>

static RandomNumberGenerator _randm;

EntityManager* EntityManager::_instance = nullptr;

EntityManager::EntityManager() : _camera(new CameraEntity())
{
    _randm.setSeed(7839);
}

EntityManager& Entity::Manager()
{
    if (EntityManager::_instance == nullptr) EntityManager::_instance = new EntityManager();

    return *EntityManager::_instance;
}

EntityManager::~EntityManager()
{ }

std::vector<Entity*> EntityManager::entitiesOfType(int type)
{
    auto result = std::vector<Entity*>();

    for (auto e : Entity::Manager()._entities) if (e->getType() == type) result.push_back(e);

    return result;
}

glm::vec2 EntityManager::worldToScreen(const glm::vec3& pos) const
{
    if (this->_camera != nullptr)
    {
        auto res = glm::project(pos, this->_camera->getCameraMatrix(), this->_lastProj, this->_camera->viewport());
        auto r = glm::vec2(res.x, this->_camera->viewport().w - res.y);
        return r;
    }

    return glm::vec2(pos.x, pos.y);
}

void EntityManager::init()
{
    this->_camera->setMatrix(glm::lookAt(
                glm::vec3(-30.0f, 0.0f, 15.0f),
                glm::vec3(0.0f, 0.0f, 12.0f),
                glm::vec3(0.0f, 0.0f, 1.0f)
                ));
}

void EntityManager::update(float elapsed)
{
    this->_camera->update(elapsed);
    std::vector<Entity*> tobedeleted;
    for (auto e : Entity::Manager()._entities)
    {
        e->update(elapsed);
        if (e->isDeleted()) tobedeleted.push_back(e);
    }
    while (!tobedeleted.empty())
    {
        auto e = tobedeleted.back();
        Entity::Manager()._entities.erase(e);
        tobedeleted.pop_back();
        delete e;
    }
}

void EntityManager::render(const glm::mat4 &proj)
{
    for (auto e : this->_entities)
        e->render(proj, this->_camera->getCameraMatrix());

    this->_lastProj = proj;
}

void EntityManager::changeView()
{
    this->_camera->changeView();
}

void EntityManager::moveToTopView()
{
    this->_camera->moveToTopView();
}

void EntityManager::moveToDefaultView()
{
    this->_camera->moveToDefaultView();
}

void EntityManager::reset()
{
    Entity::Manager()._entities.clear();
}
