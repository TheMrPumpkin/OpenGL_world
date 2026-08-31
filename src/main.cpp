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
    Shader ourshader("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/src/VertexShader.vs",
                     "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/src/FragmentShader.fs");

    vertexArray.Vertexarray();
    vertexArray.cubePositions;

    Texture2D dirt_texture("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/images/dirt.jpg");
    Texture2D dirtawesomeface_texture("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_world/images/awesomeface.png");

    ourshader.use();
    glUniform1i(glGetUniformLocation(ourshader.ID, "TEXTURE1"), 0);
    ourshader.setInt("TEXTURE2", 1);

    while (!glfwWindowShouldClose(window))
    {
        camera.move(window);
        // BG
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // textures
        glActiveTexture(GL_TEXTURE0);
        dirt_texture.bind();
        glActiveTexture(GL_TEXTURE1);
        dirtawesomeface_texture.bind();

        ourshader.use();

        glm::mat4 proj = camera.perspective(screen_w, screen_h);
        unsigned int projLOC = glGetUniformLocation(ourshader.ID, "proj");
        glUniformMatrix4fv(projLOC, 1, GL_FALSE, glm::value_ptr(proj));

        // objects
        vertexArray.bind();

        for (GLuint i = 0; i < 1; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, vertexArray.cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            unsigned int modelLOC = glGetUniformLocation(ourshader.ID, "model");
            glUniformMatrix4fv(modelLOC, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glm::mat4 view = camera.GetViewMatrix();
        view = glm::lookAt(camera.cameraPos, camera.cameraFront + camera.cameraPos, camera.up);
        unsigned int viewlLOC = glGetUniformLocation(ourshader.ID, "view");
        glUniformMatrix4fv(viewlLOC, 1, GL_FALSE, glm::value_ptr(view));

        // camera.cords();
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
