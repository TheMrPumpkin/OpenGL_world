#include "OpenGLDebug.h"

void APIENTRY openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                  GLsizei length, const GLchar *message, const void *userParam)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;

    std::cout << "\n================= OpenGL Debug Event =================" << std::endl;
    std::cout << "Message: " << message << std::endl;

    std::cout << "Type: ";
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "API Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Deprecated Behavior";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Undefined Behavior";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Portability Issue";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Performance Warning";
        break;
    default:
        std::cout << "Other";
        break;
    }

    std::cout << " | Severity: ";
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "HIGH (Critical Error!)";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "MEDIUM (Bad Practice / Performance)";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "LOW (Warning)";
        break;
    }
    std::cout << "\n======================================================\n"
              << std::endl;
}

void enableOpenGLDebug()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openGLDebugCallback, nullptr);
}
