#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "shader_debug.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "OpenGLDebug.h"
#include "camera.h"
#include "Mouse.h"
#include "VertexArray.h"
#include "Texture2D.h"
#include "FileSystem.h"
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

glm::vec3 lightPos(1.2f, 0.5f, 2.3f);
glm::vec3 lightcubePositions[] = {glm::vec3(2.0f, 0.0f, 0.0f) , 
                     glm::vec3(0.9f, 9.0f, -4.0f) };
                     
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

    GLFWwindow *window = glfwCreateWindow(screen_w, screen_h, "openGL light", NULL, NULL);

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
    Shader lightshader("/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/lightshader.vs",
                       "/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/lightshader.fs");
    Shader cubelightshader("/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/cubelightshader.vs",
                           "/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/cubelightshader.fs");

    vertexArray.Vertexarray();
    vertexArray.cubePositions;

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    vertexArray.bindVBO();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    Texture2D diffuseMap(FileSystem::getPath("/images/container2.png").c_str());
    Texture2D specularMap(FileSystem::getPath("/images/container2_specular.png").c_str());


    lightshader.use();
    lightshader.setInt("material.diffuse", 0);
    lightshader.setInt("material.specular" ,1);



    while (!glfwWindowShouldClose(window))
    {
        camera.move(window);
        // BG
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        

        lightshader.use();
        lightshader.setFloat("material.shininess", 64.0f);
        lightshader.setVec3("viewPos", camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

        lightshader.setVec3("dirLight.direction", -2.0f, 0.5f, 1.0f);
        lightshader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
        lightshader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
        lightshader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);


        lightshader.setVec3("pointLights[0].position" , lightcubePositions[0].x , lightcubePositions[0].y , lightcubePositions[0].z);
        lightshader.setVec3("pointLights[0].ambient", 0.1f, 0.1f, 0.1f);
        lightshader.setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
        lightshader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightshader.setFloat("pointLights[0].constant" , 1.0f);
        lightshader.setFloat("pointLights[0].linear" , 0.09f); // small = big 
        lightshader.setFloat("pointLights[0].quadratic" , 0.032f); // small = big 



        lightshader.setVec3("pointLights[1].position" , lightcubePositions[1].x , lightcubePositions[1].y , lightcubePositions[1].z);
        lightshader.setVec3("pointLights[1].ambient", 0.1f, 0.1f, 0.1f);
        lightshader.setVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
        lightshader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightshader.setFloat("pointLights[1].constant" , 1.0f);
        lightshader.setFloat("pointLights[1].linear" , 0.09f); // small = big 
        lightshader.setFloat("pointLights[1].quadratic" , 0.032f); // small = big 

        lightshader.setVec3("spotLight.ambient", 0.1f, 0.1f, 0.1f);
        lightshader.setVec3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);
        lightshader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightshader.setFloat("spotLight.constant" , 1.0f);
        lightshader.setFloat("spotLight.linear" , 0.09f); // small = big 
        lightshader.setFloat("spotLight.quadratic" , 0.032f); // small = big 
        lightshader.setVec3("spotLight.position", camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
        lightshader.setVec3("spotLight.direction", camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z);
        lightshader.setFloat("spotLight.cutoff" , glm::cos(glm::radians(40.0f)));
        lightshader.setFloat("spotLight.outercutoff" , glm::cos(glm::radians(50.0f)));
        

        glm::mat4 view = camera.GetViewMatrix();
        lightshader.setMat4("view", view);

        glm::mat4 proj = camera.perspective(screen_w, screen_h);
        lightshader.setMat4("proj", proj);

        glActiveTexture(GL_TEXTURE1);
        specularMap.bind();
        glActiveTexture(GL_TEXTURE0);
        diffuseMap.bind();

        vertexArray.bindVAO();



         for (int i = 0; i < 5; i++)
         {
        glm::mat4 model = glm::mat4(1.0f);
        model  = glm::translate(model  , vertexArray.cubePositions[i]);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 3.0f, 2.0f));
        lightshader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

        cubelightshader.use();

        cubelightshader.setMat4("view", view);

        cubelightshader.setMat4("proj", proj);
        glBindVertexArray(lightVAO);
        for (int i = 0; i < 2; i++){
         glm::mat4 model = glm::mat4(1.0f);
          model = glm::translate(model, lightcubePositions[i]);
         model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 5.0f));
         model = glm::scale(model, glm::vec3(0.2f));
          cubelightshader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36); }

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

