#include "geometry.h"
#include "shader.h"
#include "stb_perlin.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Geometry::Geometry()
    : _shader(Geometry::shader()), _vao(0), _vbo(0), _mode(GL_TRIANGLES), _vertexCount(0)
{ }

void Geometry::init()
{
    if (this->_vao == 0)
        glGenVertexArrays(1, &this->_vao);
    glBindVertexArray(this->_vao);

    if (this->_vbo == 0)
        glGenBuffers(1, &this->_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

    auto vertexAttrib = glGetAttribLocation(this->_shader, "vertex");
    glVertexAttribPointer(GLuint(vertexAttrib), 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), 0);
    glEnableVertexAttribArray(GLuint(vertexAttrib));

    auto normalAttrib = glGetAttribLocation(this->_shader, "normal");
    glVertexAttribPointer(GLuint(normalAttrib), 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), reinterpret_cast<const GLvoid*>(sizeof(float) * 3));
    glEnableVertexAttribArray(GLuint(normalAttrib));

    auto colAttrib = glGetAttribLocation(this->_shader, "color");
    glVertexAttribPointer(GLuint(colAttrib), 3, GL_FLOAT, GL_FALSE, sizeof(tVertex), reinterpret_cast<const GLvoid*>(sizeof(float) * 6));
    glEnableVertexAttribArray(GLuint(colAttrib));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Geometry::~Geometry()
{
    // TODO : cleanup vao end vbo
}

void Geometry::setShader(GLuint shader)
{
    this->_shader = shader;
}

void Geometry::setMode(GLenum mode)
{
    this->_mode = mode;
}

void Geometry::setVertices(const std::vector<tVertex>& vertices)
{
    this->_vertexCount = vertices.size();
    glBindVertexArray(this->_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(vertices.size() * sizeof(tVertex)), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, GLsizeiptr(vertices.size() * sizeof(tVertex)), reinterpret_cast<const GLvoid*>(&vertices[0]));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Geometry::setFaces(const std::vector<tFace>& faces)
{
    this->_faces = faces;
}

void Geometry::render(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model)
{
    this->bind(projection, view, model);

    if (!this->_faces.empty())
    {
        for (auto f : this->_faces)
            glDrawArrays(this->_mode, f._start, f._count);
    }
    else
        glDrawArrays(this->_mode, 0, this->_vertexCount);

    this->unbind();
}

void Geometry::bind(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model)
{
    glUseProgram(this->_shader);
    glUniformMatrix4fv(Geometry::projectionUniform(this->_shader), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(Geometry::viewUniform(this->_shader), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(Geometry::modelUniform(this->_shader), 1, false, glm::value_ptr(model));

    glBindVertexArray(this->_vao);
}

void Geometry::unbind()
{
    glBindVertexArray(0);
}

Geometry* Geometry::createBox(const glm::vec3& size, const glm::vec3& offset)
{
    std::vector<tVertex> vertices = {
        // Front Face
        { {-size.x, -size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        { { size.x, -size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        { { size.x,  size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        { {-size.x,  size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 0.0f, 1.0f, 0.0f } }, // Top Left Of The Texture and Quad
        // Back Face
        { {-size.x, -size.y, -size.z }, {  0.0f,  0.0f, -1.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        { {-size.x,  size.y, -size.z }, {  0.0f,  0.0f, -1.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        { { size.x,  size.y, -size.z }, {  0.0f,  0.0f, -1.0f}, { 0.0f, 1.0f, 0.0f } }, // Top Left Of The Texture and Quad
        { { size.x, -size.y, -size.z }, {  0.0f,  0.0f, -1.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        // Top Face
        { {-size.x,  size.y, -size.z }, {  0.0f,  1.0f,  0.0f}, { 0.0f, 1.0f, 0.0f } }, // Top Left Of The Texture and Quad
        { {-size.x,  size.y,  size.z }, {  0.0f,  1.0f,  0.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        { { size.x,  size.y,  size.z }, {  0.0f,  1.0f,  0.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        { { size.x,  size.y, -size.z }, {  0.0f,  1.0f,  0.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        // Bottom Face
        { {-size.x, -size.y, -size.z }, {  0.0f, -1.0f,  0.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        { { size.x, -size.y, -size.z }, {  0.0f, -1.0f,  0.0f}, { 0.0f, 1.0f, 0.0f } }, // Top Left Of The Texture and Quad
        { { size.x, -size.y,  size.z }, {  0.0f, -1.0f,  0.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        { {-size.x, -size.y,  size.z }, {  0.0f, -1.0f,  0.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        // Right face
        { { size.x, -size.y, -size.z }, {  1.0f,  0.0f,  0.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        { { size.x,  size.y, -size.z }, {  1.0f,  0.0f,  0.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        { { size.x,  size.y,  size.z }, {  1.0f,  0.0f,  0.0f}, { 0.0f, 1.0f, 0.0f } }, // Top Left Of The Texture and Quad
        { { size.x, -size.y,  size.z }, {  1.0f,  0.0f,  0.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        // Left Face
        { {-size.x, -size.y, -size.z }, { -1.0f,  0.0f,  0.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        { {-size.x, -size.y,  size.z }, { -1.0f,  0.0f,  0.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        { {-size.x,  size.y,  size.z }, { -1.0f,  0.0f,  0.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        { {-size.x,  size.y, -size.z }, { -1.0f,  0.0f,  0.0f}, { 0.0f, 1.0f, 0.0f } }  // Top Left Of The Texture and Quad
    };

    std::vector<tFace> faces = {
        {  0, 4 }, {  4, 4 }, {  8, 4 },
        { 12, 4 }, { 16, 4 }, { 20, 4 }
    };

    for (auto v : vertices) {
        v.pos[0] += offset.x;
        v.pos[1] += offset.y;
        v.pos[2] += offset.z;
    }

    auto result = new Geometry();

    result->init();
    result->setMode(GL_TRIANGLE_FAN);
    result->setVertices(vertices);
    result->setFaces(faces);

    return result;
}

Geometry* Geometry::createPlane(const glm::vec3& size, const glm::vec3& offset)
{
    std::vector<tVertex> vertices = {
        // Front Face
        { {-size.x, -size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        { { size.x, -size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        { { size.x,  size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        { {-size.x,  size.y,  size.z }, {  0.0f,  0.0f,  1.0f}, { 0.0f, 1.0f, 0.0f } }, // Top Left Of The Texture and Quad
    };

    std::vector<tFace> faces = {
        {  0, 4 }
    };

    for (auto v : vertices) {
        v.pos[0] += offset.x;
        v.pos[1] += offset.y;
        v.pos[2] += offset.z;
    }

    auto result = new Geometry();

    result->init();
    result->setMode(GL_TRIANGLE_FAN);
    result->setVertices(vertices);
    result->setFaces(faces);

    return result;
}

Geometry* Geometry::createQuad(const glm::vec2& size, GLuint shader)
{
    std::vector<tVertex> vertices = {
        // Front Face
        { {   0.0f,    0.0f,  0.0f }, {  0.0f,  0.0f,  1.0f}, { 0.0f, 0.0f, 0.0f } }, // Bottom Left Of The Texture and Quad
        { { size.x,    0.0f,  0.0f }, {  0.0f,  0.0f,  1.0f}, { 1.0f, 0.0f, 0.0f } }, // Bottom Right Of The Texture and Quad
        { { size.x,  size.y,  0.0f }, {  0.0f,  0.0f,  1.0f}, { 1.0f, 1.0f, 0.0f } }, // Top Right Of The Texture and Quad
        { {   0.0f,  size.y,  0.0f }, {  0.0f,  0.0f,  1.0f}, { 0.0f, 1.0f, 0.0f } }, // Top Left Of The Texture and Quad
    };

    std::vector<tFace> faces = {
        { 0, 4 }
    };

    auto result = new Geometry();

    result->setShader(shader);
    result->init();
    result->setMode(GL_TRIANGLE_FAN);
    result->setVertices(vertices);
    result->setFaces(faces);

    return result;
}

const static float _pi = 3.141592653589793238462643383279502884f;

Geometry* Geometry::createSphere(float radius, const glm::vec3& offset)
{
    return Geometry::createBall(glm::vec3(radius), offset);
}

void createLatVertices(int i, int lats, int longs, const glm::vec3& size, const glm::vec3& offset, std::vector<tVertex>& vertices, std::vector<tFace>& faces)
{
    float lat0 = _pi * (-0.5f + float(i - 1) / lats);
    float z0  = float(sin(lat0));
    float zr0 =  float(cos(lat0));

    float lat1 = _pi * (-0.5f + float(i) / lats);
    float z1 = float(sin(lat1));
    float zr1 = float(cos(lat1));

    tFace f = { static_cast<GLsizei>(vertices.size()), 0};

    for(int j = 0; j <= longs; j++)
    {
       float lng = 2.0f * _pi * float(j - 1) / longs;
       float x = float(cos(lng));
       float y = float(sin(lng));

       tVertex v1 = {
           { offset.x + (size.x * x * zr0), offset.y + (size.y * y * zr0), offset.z + (size.z * z0) },
           { x * zr0, y * zr0, z0 },
           { float(j) / float(longs), float(i) / float(lats), 0.0f }
       };
       vertices.push_back(v1);
       f._count++;

       tVertex v2 = {
           { offset.x + (size.x * x * zr1), offset.y + (size.y * y * zr1), offset.z + (size.z * z1) },
           { x * zr1, y * zr1, z1 },
           { float(j) / float(longs), float(i+1) / float(lats), 0.0f }
       };
       vertices.push_back(v2);
       f._count++;
    }

    faces.push_back(f);
}

Geometry* Geometry::createBall(const glm::vec3& size, const glm::vec3& offset)
{
    std::vector<tVertex> vertices;
    std::vector<tFace> faces;

    int lats = 32, longs = 32;

    for(int i = 0; i <= lats; i++)
    {
        createLatVertices(i, lats, longs, size, offset, vertices, faces);
    }

    auto result = new Geometry();

    result->init();
    result->setMode(GL_TRIANGLE_STRIP);
    result->setVertices(vertices);
    result->setFaces(faces);

    return result;
}

Geometry* Geometry::createCapsule(float radius, float height, const glm::vec3& offset)
{
    glm::vec3 size = glm::vec3(radius);
    std::vector<tVertex> vertices;
    std::vector<tFace> faces;

    int lats = 32, longs = 32;

    for(int i = 0; i <= (lats / 2); i++)
    {
        createLatVertices(i, lats, longs, size, glm::vec3(offset.x, offset.y, offset.z - (height / 2.0f)), vertices, faces);
    }

    {
        int i = (lats / 2);
        float lat0 = _pi * (-0.5f + float(i - 1) / lats);
        float z0  = float(sin(lat0));
        float zr0 =  float(cos(lat0));

        tFace f = { static_cast<GLsizei>(vertices.size()), 0 };

        for(int j = 0; j <= longs; j++)
        {
           float lng = 2.0f * _pi * float(j - 1) / longs;
           float x = float(cos(lng));
           float y = float(sin(lng));

           tVertex v1 = {
               { offset.x + (size.x * x * zr0), offset.y + (size.y * y * zr0), offset.z - (height / 2.0f) + (size.z * z0) },
               { x * zr0, y * zr0, z0 },
               { float(j) / float(longs), float(i+1) / float(lats), 0.0f }
           };
           vertices.push_back(v1);
           f._count++;

           tVertex v2 = {
               { offset.x + (size.x * x * zr0), offset.y + (size.y * y * zr0), offset.z + (height / 2.0f) + (size.z * z0) },
               { x * zr0, y * zr0, z0 },
               { float(j) / float(longs), float(i-1) / float(lats) / 2.0f, 0.0f }
           };
           vertices.push_back(v2);
           f._count++;
        }

        faces.push_back(f);
    }

    for(int i = lats / 2; i <= lats; i++)
    {
        createLatVertices(i, lats, longs, size, glm::vec3(offset.x, offset.y, offset.z + (height / 2.0f)), vertices, faces);
    }

    auto result = new Geometry();

    result->init();
    result->setMode(GL_TRIANGLE_STRIP);
    result->setVertices(vertices);
    result->setFaces(faces);

    return result;
}

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

float noise_forest(int x, int y)
{
    return (stb_perlin_noise3(float(x) / layer_forest, float(y) / layer_forest, 0) + 1.0f) / 2.0f;
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

#define GEN_VERTEX(x, y) glm::vec3(float(x) * 8.0f, float(y) * 8.0f, 0.0f)
#define GEN_COLOR(x, y, t) noise(x, y) * falloff(x, y, t), noise_forest(x, y), distance(x, y, t)

void fix_color(float* f_color)
{
    if (f_color[0] < 0.6f)
    {
        f_color[0] = 163.0f/255.0f;
        f_color[1] = 204.0f/255.0f;
        f_color[2] = 255.0f/255.0f;
    }
    else if (f_color[0] < 0.64f)
    {
        f_color[0] = 250.0f/255.0f;
        f_color[1] = 242.0f/255.0f;
        f_color[2] = 199.0f/255.0f;
    }
    else if (f_color[0] < 0.67f)
    {
        f_color[0] = 240.0f/255.0f;
        f_color[1] = 237.0f/255.0f;
        f_color[2] = 229.0f/255.0f;
    }
    else
    {
        if (f_color[1] > 0.5f)
        {
            f_color[0] = 240.0f/255.0f;
            f_color[1] = 237.0f/255.0f;
            f_color[2] = 229.0f/255.0f;
        }
        else
        {
            f_color[0] = 210.0f/255.0f;
            f_color[1] = 228.0f/255.0f;
            f_color[2] = 200.0f/255.0f;
        }
    }
}

Geometry* Geometry::createTerrain()
{
    int tileCount = 256;
    float multiplier = 150.0f;
    float halfmultiplier = multiplier / 2.0f;

    std::vector<tVertex> heightMap;
    const float tileStep = 1;
    for (int y = -(tileCount / 2); y < (tileCount / 2); y += tileStep)
    {
        for (int x = -(tileCount / 2); x < (tileCount / 2); x+= tileStep)
        {
            auto a = GEN_VERTEX(x, y);
            auto b = GEN_VERTEX(x + tileStep, y);
            auto c = GEN_VERTEX(x, y + tileStep);
            auto d = GEN_VERTEX(x + tileStep, y + tileStep);

            auto n = glm::normalize(glm::cross(b-a, c-a));

            tVertex v1 = {
                { a.x, a.y, a.z },
                { n.x, n.y, n.z },
                { GEN_COLOR(x, y, tileCount) }
            };
//            fix_color(v1.col);
            tVertex v2 = {
                { b.x, b.y, b.z },
                { n.x, n.y, n.z },
                { GEN_COLOR(x + tileStep, y, tileCount) }
            };
//            fix_color(v2.col);
            tVertex v3 = {
                { c.x, c.y, c.z },
                { n.x, n.y, n.z },
                { GEN_COLOR(x, y + tileStep, tileCount) }
            };
//            fix_color(v3.col);
            tVertex v4 = {
                { d.x, d.y, d.z },
                { n.x, n.y, n.z },
                { GEN_COLOR(x + tileStep, y + tileStep, tileCount) }
            };
//            fix_color(v4.col);

            heightMap.push_back(v1);
            heightMap.push_back(v2);
            heightMap.push_back(v3);

            n = glm::normalize(glm::cross(d-b, c-b));
            for (int i = 0; i < 3; i++)
                v2.nor[i] = v3.nor[i] = v4.nor[i] = n[i];

            heightMap.push_back(v2);
            heightMap.push_back(v4);
            heightMap.push_back(v3);
        }
    }

    auto floor = new Geometry();
    floor->init();
    floor->setVertices(heightMap);
    floor->setMode(GL_TRIANGLES);
    return floor;
}

static GLuint geomShader = 0;

GLuint Geometry::shader()
{
    if (geomShader == 0)
        geomShader = LoadShaderProgram("geometry");

    return geomShader;
}

static GLint _projectionUniform = 0;

GLint Geometry::projectionUniform(GLuint shader)
{
    if (_projectionUniform == 0)
        _projectionUniform = glGetUniformLocation(shader, "u_p");

    return _projectionUniform;
}

static GLint _viewUniform = 0;

GLint Geometry::viewUniform(GLuint shader)
{
    if (_viewUniform == 0)
        _viewUniform = glGetUniformLocation(shader, "u_v");

    return _viewUniform;
}

static GLint _modeluniform = 0;

GLint Geometry::modelUniform(GLuint shader)
{
    if (_modeluniform == 0)
        _modeluniform = glGetUniformLocation(shader, "u_m");

    return _modeluniform;
}
