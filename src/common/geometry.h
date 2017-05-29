#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../system/platform-opengl.h"
#include <glm/glm.hpp>
#include <vector>
#include <functional>

typedef struct sVertex
{
    float pos[3];
    float nor[3];
    float col[3];

    sVertex(const glm::vec3& pos, const glm::vec3& nor, const glm::vec3& col)
    {
        for (int i = 0; i < 3; i++)
        {
            this->pos[i] = pos[i];
            this->nor[i] = nor[i];
            this->col[i] = col[i];
        }
    }

    sVertex& operator = (const sVertex& orig)
    {
        for (int i = 0; i < 3; i++)
        {
            this->pos[i] = orig.pos[i];
            this->nor[i] = orig.nor[i];
            this->col[i] = orig.col[i];
        }

        return (*this);
    }

} tVertex;

typedef struct sFace
{
    GLint _start;
    GLsizei _count;

} tFace;

class Geometry
{
    static GLuint shader();
    static GLint projectionUniform(GLuint shader);
    static GLint viewUniform(GLuint shader);
    static GLint modelUniform(GLuint shader);
    static GLint colorUniform(GLuint shader);

    GLuint _shader;
    GLuint _vao;
    GLuint _vbo;
    GLenum _mode;
    int _vertexCount;
    std::vector<tFace> _faces;

public:
    Geometry();
    virtual ~Geometry();

    void init();
    virtual void render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);

    void bind(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);
    void unbind();

    void setShader(GLuint shader);
    void setMode(GLenum mode);
    void setVertices(const std::vector<tVertex>& vertices);
    void setFaces(const std::vector<tFace>& faces);

public:
    static Geometry* createSphere(float radius, const glm::vec3& offset = glm::vec3());
    static Geometry* createBall(const glm::vec3& size, const glm::vec3& offset = glm::vec3());
    static Geometry* createCapsule(float radius, float height, const glm::vec3& offset = glm::vec3());
    static Geometry* createBox(const glm::vec3& size, const glm::vec3& offset = glm::vec3());
    static Geometry* createPlane(const glm::vec3& size, const glm::vec3& offset);
    static Geometry* createQuad(const glm::vec2& size, GLuint shader);
    static Geometry* createQuad2(const glm::vec2& size, GLuint shader);
    static Geometry* createTerrain(int tileCount, int tileStep, std::function<glm::vec3 (int x, int y)> genposition, std::function<glm::vec3 (int x, int y)> gencolor);
};

#endif // _GEOMETRY_H_
