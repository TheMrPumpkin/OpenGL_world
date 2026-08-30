#ifndef MOUSE_CLASS_H
#define MOUSE_CLASS_H
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mouse
{

public:
    GLuint ID;

    Mouse();
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    float lastX;
    float lastY;
    bool firstMouse;
    void SetCursorPosCallback(GLFWwindow *window);
    void SetScrollCallback(GLFWwindow *window);
    void SetInputMode(GLFWwindow *window);
};

#endif
