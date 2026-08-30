#ifndef OPENGL_DEBUG_H
#define OPENGL_DEBUG_H

#include <glad/glad.h>
#include <iostream>

void APIENTRY openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                  GLsizei length, const GLchar *message, const void *userParam);

void enableOpenGLDebug();

#endif
