
//#define STB_IMAGE_IMPLEMENTATION
#include "../common/stb_image.h"

#define STB_PERLIN_IMPLEMENTATION
#include "../common/stb_perlin.h"

#ifdef _WIN32

#define GLEXTL_IMPLEMENTATION
#include <GL/glextl.h>
#define NANOVG_GL3_IMPLEMENTATION

#endif // _WIN32

#ifdef linux

#ifndef __ANDROID__
#include <GL/glew.h>
#define NANOVG_GL2_IMPLEMENTATION
#endif // __ANDROID__

#endif // linux

#ifdef __ANDROID__

#include <GLES/gl.h>
#include <GLES3/gl3.h>
#define NANOVG_GLES3_IMPLEMENTATION

#endif // __ANDROID__

#include "nanovg.h"
#include "nanovg_gl.h"
