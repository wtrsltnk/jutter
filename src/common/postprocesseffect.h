#ifndef POSTPROCESSEFFECT_H
#define POSTPROCESSEFFECT_H

#include "../system/platform-opengl.h"
#include "geometry.h"
#include <functional>

class PostProcessEffect
{
    GLuint _frameBuffer;
    GLuint _texColorBuffer;
    GLuint _texDepthBuffer;
    GLuint _rboDepth;
    GLuint _shader;
    int _width;
    int _height;
    Geometry* _geometry;

public:
    PostProcessEffect();
    virtual ~PostProcessEffect();

    void setup(int width, int height);
    void captureBuffer();
    void capture(std::function<void()> f);
    void endCaptureBuffer();
    void renderEffect();
    void cleanup();

};

#endif // POSTPROCESSEFFECT_H
