#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_project2/include/shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_project2/include/stb_image.h"
#include "OpenGLDebug.h"
#include "camera.h"
#include "Mouse.h"
#include "VertexArray.h"
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
    Shader ourshader("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_project2/src/OpenGL_world/VertexShader.vs",
                     "/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_project2/src/OpenGL_world/FragmentShader.fs");

    vertexArray.Vertexarray();
    vertexArray.cubePositions;

    GLuint Texture1, Texture2;
    glGenTextures(1, &Texture1);
    glGenTextures(1, &Texture2);
    glBindTexture(GL_TEXTURE_2D, Texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    int w, h, nchanel;
    unsigned char *data = stbi_load("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_project2/images/dirt.jpg", &w, &h, &nchanel, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Texture error!(1)" << std::endl;
        glfwTerminate();
        return -1;
    }

    glBindTexture(GL_TEXTURE_2D, Texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    data = stbi_load("/home/Mrpumpkin/Documents/VSC/OpenGL/OpenGL_project2/images/awesomeface.png", &w, &h, &nchanel, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Texture error!(2)" << std::endl;
        glfwTerminate();
        return -1;
    }

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
        glBindTexture(GL_TEXTURE_2D, Texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture2);

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
