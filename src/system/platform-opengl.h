
#ifdef _WIN32

#include <GL/glextl.h>

#endif // _WIN32

#ifdef __ANDROID__

#include <GLES/gl.h>
#include <GLES3/gl3.h>

#endif // __ANDROID__

#ifdef linux

#ifndef __ANDROID__
#include <GL/glew.h>
#endif // __ANDROID__

#endif // linux

#ifndef nullptr
#define nullptr NULL 
#endif
