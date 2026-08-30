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
#include "camera.h"
#include "Mouse.h"

extern Camera camera;

Mouse::Mouse()
{
    lastX = 475;
    lastY = 450;
    firstMouse = true;
}

void SetInputMode(GLFWwindow *window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor
}

void Mouse::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX; // calculate the offset movement between the last and current frame
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.2f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    camera.yaw += xoffset;
    camera.pitch -= yoffset;

    if (camera.pitch > 89.0f)
    {
        camera.pitch = 89.0f;
    }
    if (camera.pitch < -89.0f)
    {
        camera.pitch = -89.0f;
    }

    camera.rotate();
}

void Mouse::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.fov -= (float)yoffset;
    if (camera.fov < 1.0f)
    {
        camera.fov = 1.0f;
    }
    if (camera.fov > 90.0f)
    {
        camera.fov = 90.0f;
    }
}