#ifndef OGL_DEBUG_HPP
#define OGL_DEBUG_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
{

GLenum glCheckError(const char *file, int line);

}

#define GL_ERROR_CHECK() OGLSample::glCheckError(__FILE__, __LINE__)
//#define GL_ERROR_CHECK()

#endif
