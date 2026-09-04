#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/include/shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/include/stb_image.h"
#include "OpenGLDebug.h"
#include "camera.h"
#include "Mouse.h"
#include "VertexArray.h"
#include "Texture2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int screen_w = 950;
const unsigned int screen_h = 850;

// camera
Camera camera;
// Mouse
Mouse mouse;
// VertexArray
VertexArray vertexArray;

glm::vec3 lightPos(5.0, 2.0, 0.0);

void frame_buffer_callback(GLFWwindow *window, int w, int h);
void input_press(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(screen_w, screen_h, "openGL GLM ", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "window error!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD error!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    Shader cubeshader("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/src/CubeShader.vs",
                      "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/src/CubeShader.fs");
    Shader cubelightshader("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/src/cubelightshader.vs",
                           "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/src/cubelightshader.fs");

    vertexArray.Vertexarray();
    vertexArray.cubePositions;

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    vertexArray.bindVBO();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture2D dirt_texture("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/images/dirt.jpg");
    // Texture2D dirtawesomeface_texture("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/images/awesomeface.png");

    while (!glfwWindowShouldClose(window))
    {
        camera.move(window);
        // BG
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeshader.use();
        cubeshader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        cubeshader.setVec3("lightColor", 0.0f, 0.85f, 0.65f);

        glm::mat4 view = camera.GetViewMatrix();
        cubeshader.setMat4("view", view);

        glm::mat4 proj = camera.perspective(screen_w, screen_h);
        cubeshader.setMat4("proj", proj);

        vertexArray.bindVAO();
        glm::mat4 model = glm::mat4(1.0f);
        cubeshader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        cubelightshader.use();

        cubelightshader.setMat4("view", view);

        cubelightshader.setMat4("proj", proj);

        model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        cubelightshader.setMat4("model", model);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        camera.cords();

        // window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
void frame_buffer_callback(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    mouse.mouse_callback(window, xpos, ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    mouse.scroll_callback(window, xoffset, yoffset);
}