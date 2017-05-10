#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "shader.h"
#include <glm/glm.hpp>
#include <set>

enum class ParticleTypes
{
    Square = 0,
    Glow = 1
};

class Particle
{
public:
    Particle();
    virtual ~Particle();

    void Update(float ticks);

    glm::vec3 _pos;
    glm::vec3 _direction;
    glm::vec4 _color;
    ParticleTypes _type;
    float _size;
    int _state;			// dead = 0, spawning, alive, dying
    float _spawnSpeed;
    float _dieSpeed;
};

class ParticleTrail
{
    friend class Particles;
    bool _active;
    class Entity* _entity;
    float _lastAddAt;

    ParticleTrail();
public:
    virtual ~ParticleTrail();

    void Update(float ticks);
};

class Particles
{
    Particles(int particleCount = 50);
    static Particles* _instance;
public:
    static Particles& Manager();
    virtual ~Particles();

    Particle* AddParticle(const glm::vec3& pos);
    void AddExplosion(const glm::vec3& pos, int count);
    void StartTrail(class Entity* entity);
    void EndTrail(class Entity* entity);

    bool Init();
    void Update(float ticks);
    void Render(const glm::mat4 & proj, const glm::mat4 & view);

private:
    glm::vec3 pos;
    std::set<Particle*> activeParticles;
    std::set<Particle*> inactiveParticles;
    Particle* popInactiveParticle();
    void deactivateParticle(Particle* particle);

    std::set<ParticleTrail*> activeParticleTrails;
    std::set<ParticleTrail*> inactiveParticleTrails;
    ParticleTrail* popInactiveParticleTrail();
    void deactivateParticleTrail(ParticleTrail* particleTrail);

    static bool SetupShader();
    static bool SetupTexture();

    static GLuint program;
    static GLuint textures[2];
    static GLuint a_vertex;
    static GLuint a_texcoord;
    static GLuint u_projection;
    static GLuint u_view;
    static GLuint u_model;
    static GLuint u_global_color;
    static GLuint u_sprite_size;
    static GLuint u_tex;

};

#endif				// _PARTICLES_H_
