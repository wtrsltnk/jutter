#include "worldentity.h"
#include "../common/geometry.h"
#include "../common/stb_perlin.h"

#include <random>

const int WorldEntity::Type = 8;

Geometry* WorldEntity::_worldGeom = nullptr;

const int offsetx = 100;
const int offsety = -50;
const float layer_forest = 9.0f;
const float layer1 = 25.0f;
const float layer2 = 180.0f;

float noise(int x, int y)
{
    float xx = float(x + offsetx);
    float yy = float(y + offsety);
    return
            (
                ((stb_perlin_noise3(xx / layer1, yy / layer1, 0) + 1.0f) / 2.0f) +
                ((stb_perlin_noise3(xx / layer2, yy / layer2, 0) + 1.0f) / 2.0f)
            ) / 2.0f;
}

float distance(int x, int y, int max)
{
    return glm::length(glm::vec2(float(x), float(y))) / (float(max) / 2.0f);
}

float falloff(int x, int y, int max)
{
    auto d = distance(x, y, max);
    return glm::min(1.0f, 1.6f - glm::sqrt(d * d));
}

float noise_forest(int x, int y)
{
    return (stb_perlin_noise3(float(x) / layer_forest, float(y) / layer_forest, 0) + 1.0f) / 2.0f;
}

WorldEntity::WorldEntity()
{
    if (WorldEntity::_worldGeom == nullptr)
    {
        WorldEntity::_worldGeom = Geometry::createTerrain(256, 4, [] (int x, int y) -> glm::vec3 {
            return glm::vec3(float(x) * 8.0f, float(y) * 8.0f, 0.0f);
        }, [] (int x, int y) -> glm::vec3 {
            return glm::vec3(noise(x, y) * falloff(x, y, 256), noise_forest(x, y), 0.0f);
        });
    }

    this->attachGeometryProperty(WorldEntity::_worldGeom);
}

WorldEntity::~WorldEntity()
{ }

int WorldEntity::getType()
{
    return WorldEntity::Type;
}

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 256);

bool IsPointOnBeach(int x, int y)
{
    auto val = noise(x, y) * falloff(x, y, 256);
    return (val >= 0.6f && val <= 0.64f);
}

glm::vec3 WorldEntity::RandomPointOnBeach()
{
    int x = distribution(generator);
    int y = distribution(generator);

    while (!IsPointOnBeach(x, y))
    {
        x = distribution(generator);
        y = distribution(generator);
    }

    return glm::vec3(float(x), float(y), 0.0f);
}
