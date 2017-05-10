#include "particles.h"
#include "../entities/entity.h"

#include <vector>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

void Update(float ticks);
Particle::Particle()
    : _color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), _state(0), _size(1.0f), _type(ParticleTypes::Square),
      _spawnSpeed(5.0f), _dieSpeed(1.0f)
{ }

Particle::~Particle()
{ }

static GLfloat particleVertices[][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};

static GLfloat particleTexcoords[][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {1, 1, 0},
    {0, 1, 0},
};

void Particle::Update(float dt)
{
    this->_pos += (this->_direction * dt);
    this->_direction *= 1.0f - (0.05f * dt);
    if (this->_state == 1)	// spawning
    {
        this->_color.w += (dt * this->_spawnSpeed);

        if (this->_color.w >= 1.0f)
        {
            this->_color.w = 1.0f;
            this->_state = 2;	// alive
        }
    }
    else if (this->_state == 2)	// alive
    {
        this->_color.w -= (dt * this->_dieSpeed);
        if (this->_color.w < 0.0f)
        {
            this->_state = 0;	// dead
        }
    }
}

ParticleTrail::ParticleTrail() : _entity(nullptr), _active(false), _lastAddAt(0.0f) { }

ParticleTrail::~ParticleTrail() { }

void ParticleTrail::Update(float ticks)
{
    this->_lastAddAt += ticks;
    if (this->_active && this->_entity != nullptr && this->_lastAddAt > 1.0f / 60.0f)
    {
        Particles::Manager().AddParticle(this->_entity->getPosition());
        this->_lastAddAt = 0.0f;
    }
}

#ifdef __ANDROID__

namespace local_random
{

    static std::vector<int> random_numbers = {
        371, 501,  41, 539, 977,
        224, 977, 399, 776, 882,
        286, 243, 972, 781, 203,
        520, 587, 302, 877, 800,
         30, 479, 555, 815,  62,
        112, 513, 361, 332, 444,
        402,  95, 419, 722, 553,
        781, 445, 649,  36, 766,
        296, 100, 749, 310, 477,
        473, 245, 839, 774, 113,
        997, 422, 575, 163, 709,
        531,  10, 103, 960,  63,
        557, 981, 754, 919, 475,
        276, 587, 948, 850, 648,
        734, 918, 321, 815, 660,
        262, 143, 816, 457, 724,
        554,  52, 865, 891, 552,
        161, 595, 300, 101, 794,
        998, 950,  51, 182, 171,
        791, 311, 468, 320,  27,
    };

    int rand()
    {
        static std::vector<int>::iterator itr = random_numbers.begin();

        if (++itr == random_numbers.end()) itr = random_numbers.begin();

        return *itr;
    }

}
using namespace local_random;

#endif // __ANDROID__

Particles::Particles(int particleCount)
{
    for (int i = 0; i < particleCount; i++)
    {
        auto p = new Particle();
        this->inactiveParticles.insert(p);
    }
    this->SetupShader();
    this->SetupTexture();
}

Particles* Particles::_instance;

Particles& Particles::Manager()
{
    if (Particles::_instance == nullptr) Particles::_instance = new Particles();
    return *Particles::_instance;
}

Particles::~Particles()
{ }

bool Particles::Init()
{
    return (this->SetupShader() && this->SetupTexture());
}

bool Particles::SetupShader()
{
    if (Particles::program == 0)
    {
        Particles::program = LoadShaderProgram("particles");
        if (Particles::program == 0)
        {
            return false;
        }
        glUseProgram(Particles::program);

        Particles::a_vertex = glGetAttribLocation(Particles::program, "a_vertex");
        Particles::a_texcoord = glGetAttribLocation(Particles::program, "a_texcoord");
        Particles::u_projection = glGetUniformLocation(Particles::program, "u_projection");
        Particles::u_view = glGetUniformLocation(Particles::program, "u_view");
        Particles::u_model = glGetUniformLocation(Particles::program, "u_model");
        Particles::u_global_color = glGetUniformLocation(Particles::program, "u_global_color");
        Particles::u_sprite_size = glGetUniformLocation(Particles::program, "u_sprite_size");
        Particles::u_tex = glGetUniformLocation(Particles::program, "u_tex");
    }

    return true;
}

bool Particles::SetupTexture()
{
    if (Particles::textures[0] == 0)
    {
        glGenTextures(2, Particles::textures);

        const int bitmapsize = 32;
        GLubyte bitmap[bitmapsize * bitmapsize];
        for (int y = 0; y < bitmapsize; y++)
        {
            for (int x = 0; x < bitmapsize; x++)
            {
                auto v = glm::length(glm::vec2(x - (bitmapsize / 2), y - (bitmapsize / 2))) / 18.0f;
                if (v > 1.0f)
                    v = 1.0f;
                bitmap[(bitmapsize * y) + x] = (GLubyte) (255.0f/* * (1.0f - v)*/);
            }
        }

        glBindTexture(GL_TEXTURE_2D, Particles::textures[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, bitmapsize, bitmapsize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        for (int y = 0; y < bitmapsize; y++)
        {
            for (int x = 0; x < bitmapsize; x++)
            {
                auto v = glm::length(glm::vec2(x - (bitmapsize / 2), y - (bitmapsize / 2))) / 18.0f;
                if (v > 1.0f)
                    v = 1.0f;
                bitmap[(bitmapsize * y) + x] = (GLubyte) (255.0f * (1.0f - v));
            }
        }

        glBindTexture(GL_TEXTURE_2D, Particles::textures[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, bitmapsize, bitmapsize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    return true;
}

Particle* Particles::popInactiveParticle()
{
    Particle* particle = nullptr;

    if (this->inactiveParticles.empty())
    {
        particle = new Particle();
    }
    else
    {
        particle = *this->inactiveParticles.begin();
        this->inactiveParticles.erase(particle);
    }

    return particle;
}

void Particles::deactivateParticle(Particle* particle)
{
    particle->_state = 0;
    this->activeParticles.erase(particle);
    this->inactiveParticles.insert(particle);
}

ParticleTrail* Particles::popInactiveParticleTrail()
{
    ParticleTrail* trail;

    if (this->inactiveParticleTrails.empty())
    {
        trail = new ParticleTrail();
    }
    else
    {
        trail = *this->inactiveParticleTrails.begin();
        this->inactiveParticleTrails.erase(trail);
    }

    trail->_active = true;
    this->activeParticleTrails.insert(trail);

    return trail;
}

void Particles::deactivateParticleTrail(ParticleTrail* particleTrail)
{
    particleTrail->_active = false;
    this->activeParticleTrails.erase(particleTrail);
    this->inactiveParticleTrails.insert(particleTrail);
}

Particle* Particles::AddParticle(const glm::vec3& pos)
{
    auto particle = this->popInactiveParticle();

    particle->_state = 1;
    particle->_color = glm::vec4(0.5f, 0.7f, 1.0f, 1.0f);
    particle->_pos = pos;
    particle->_type = ParticleTypes::Glow;
    particle->_size = 2.0f;
    particle->_direction = glm::vec3(0.0f);
    particle->_spawnSpeed = 5.0f;
    particle->_dieSpeed = 1.0f;

    this->activeParticles.insert(particle);

    return particle;
}

void Particles::AddExplosion(const glm::vec3 & pos, int count)
{
    this->pos = pos;

    for (int i = 0; i < count; i++)
    {
        auto particle = this->popInactiveParticle();

        particle->_state = 1;
        particle->_color = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
        particle->_pos = pos;
        particle->_type = ParticleTypes::Square;
        auto x = (float(rand() % 100) - 50.0f) * 0.3f;
        auto y = (float(rand() % 100) - 50.0f) * 0.3f;
        auto z = (float(rand() % 100) - 50.0f) * 0.3f;
        particle->_direction = glm::vec3(x, y, z);
        particle->_spawnSpeed = 5.0f;
        particle->_dieSpeed = 1.0f;

        this->activeParticles.insert(particle);
    }
}

void Particles::StartTrail(class Entity* entity)
{
    auto result = this->popInactiveParticleTrail();

    result->_entity = entity;
    result->_active = true;
}

void Particles::EndTrail(class Entity* entity)
{
    for (auto trail : this->activeParticleTrails)
    {
        if (trail->_entity == entity)
        {
            this->deactivateParticleTrail(trail);
            break;
        }
    }
}

void Particles::Update(float ticks)
{
    std::set<Particle*> deactivateThese;
    for (Particle* particle : this->activeParticles)
    {
        particle->Update(ticks);
        if (particle->_state == 0) deactivateThese.insert(particle);
    }

    while (!deactivateThese.empty())
    {
        auto tmp = *deactivateThese.begin();
        deactivateThese.erase(tmp);
        this->deactivateParticle(tmp);
    }

    std::set<ParticleTrail*> deactivateTheseTrails;
    for (ParticleTrail* trail : this->activeParticleTrails)
    {
        trail->Update(ticks);
        if (!trail->_active) deactivateTheseTrails.insert(trail);
    }

    while (!deactivateTheseTrails.empty())
    {
        auto tmp = *deactivateTheseTrails.begin();
        deactivateTheseTrails.erase(tmp);
        this->deactivateParticleTrail(tmp);
    }
}

void Particles::Render(const glm::mat4 & proj, const glm::mat4 & view)
{
    glUseProgram(Particles::program);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT_AND_BACK);

    glUniformMatrix4fv(Particles::u_projection, 1, false, glm::value_ptr(proj));
    glUniformMatrix4fv(Particles::u_view, 1, false, glm::value_ptr(view));

    glVertexAttribPointer(Particles::a_vertex, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) particleVertices);
    glEnableVertexAttribArray(Particles::a_vertex);

    glVertexAttribPointer(Particles::a_texcoord, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) particleTexcoords);
    glEnableVertexAttribArray(Particles::a_texcoord);

    glUniform1i(Particles::u_tex, 0);

    for (Particle* particle : this->activeParticles)
    {
        if (particle->_state > 0)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, Particles::textures[int(particle->_type)]);

            auto localmodel = glm::translate(glm::mat4(1.0f), particle->_pos);
            glUniformMatrix4fv(Particles::u_model, 1, false, glm::value_ptr(localmodel));
            glUniform4fv(Particles::u_global_color, 1, glm::value_ptr(particle->_color));
            glUniform1f(Particles::u_sprite_size, particle->_size);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
    }
    glDisable(GL_BLEND);
}

GLuint Particles::program = 0;
GLuint Particles::textures[] = { 0, 0 };
GLuint Particles::a_vertex = 0;
GLuint Particles::a_texcoord = 0;
GLuint Particles::u_projection = 0;
GLuint Particles::u_view = 0;
GLuint Particles::u_model = 0;
GLuint Particles::u_global_color = 0;
GLuint Particles::u_sprite_size = 0;
GLuint Particles::u_tex = 0;
