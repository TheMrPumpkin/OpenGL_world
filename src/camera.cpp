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
#include "shader.h"

Camera::Camera()
{ // drop here all the data

    yaw = -90.0f;
    pitch = 0.0f;
    fov = 90.0f;
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // cameraPos
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // where the camera start see
}

glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraFront + cameraPos, up);
    return view;
}

glm::mat4 Camera::perspective(int screen_w, int screen_h)
{
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(fov), (float)screen_w / screen_h, 0.1f, 100.0f);
    return proj;
}

void Camera::rotate() // when this is rotate
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::move(GLFWwindow *window) // when this is move
{
    cam_speed = 0.05f;
    std::cout << "cam speed: " << cam_speed << std::endl;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cam_speed * cameraFront; // forward
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cam_speed * cameraFront; // move backward
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, up)) * cam_speed; // move left only Direction
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, up)) * cam_speed; // move right only Direction
    }
}

void Camera::cords()
{
    std::cout << " cameraPos | X | " << cameraPos.x << " cameraPos | Y | " << cameraPos.y << " cameraPos | Z | " << cameraPos.z << std::endl;
}