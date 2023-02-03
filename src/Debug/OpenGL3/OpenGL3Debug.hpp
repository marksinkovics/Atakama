#ifndef ATAKAMA_OPENGL3_DEBUG_HPP
#define ATAKAMA_OPENGL3_DEBUG_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Atakama
{

GLenum glCheckError(const char *file, int line);
bool CheckFrameBufferStatus(GLuint fbo);
std::string convertInternalFormatToString(GLenum format);
std::string getTextureParameters(GLuint id);
std::string getRenderbufferParameters(GLuint id);
void printFramebufferInfo(GLuint fbo);

}

#define GL_ERROR_CHECK() Atakama::glCheckError(__FILE__, __LINE__)
//#define GL_ERROR_CHECK()

#endif
