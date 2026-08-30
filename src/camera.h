#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
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
#include "shader.h"

class Camera
{

public:
    GLuint ID;

    glm::vec3 cameraPos; // cameraPos
    float yaw;
    float pitch;
    float cam_speed;
    glm::vec3 up;
    glm::vec3 cameraFront; // where the camera start see
    glm::vec3 direction;   // where i see
    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 GetViewMatrix();
    glm::mat4 perspective(int screen_w, int screen_h);

    float fov;
    float sensitivity;
    Camera();
    void move(GLFWwindow *window);

    void rotate();

    void cords();
};

#endif