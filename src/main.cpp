#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "shader_debug.h"
#include "camera.h"
#include "Mouse.h"
#include "OpenGLDebug.h"
#include "VertexArray.h"
#include "Texture2D.h"
#include "FileSystem.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "fpscounter.h"
#include "shadersmenu.h"

const unsigned int screen_w = 950;
const unsigned int screen_h = 850;

// camera
Camera camera;
// Mouse
Mouse mouse;
// VertexArray
VertexArray vertexArray;
// Shader properties menu
Shaders_menu shaderMenu;
glm::vec3 lightPos(1.2f, 0.5f, 2.3f);

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
    enableOpenGLDebug();
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange; // we own the cursor (ESC)
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 440");

    Fps_counter fpsCounter;
    //Shader lightshader("/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/lightshader.vs",
                       //"/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/lightshader.fs");
    Shader cubelightshader("/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/lightcube.vs",
                           "/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/lightcube.fs");
    Shader ModelShader("/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/model.vs" ,
         "/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/model.fs",
        "/home/pumpkin/Documents/Code and Development/OpenGL_world/include/shaders/light.glsl");

    vertexArray.Vertexarray();
    vertexArray.cubePositions;

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    vertexArray.bindVBO();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    Model mycoolModel("/home/pumpkin/Documents/Code and Development/OpenGL_world/include/Models/sonichu-medallion-chris-chan-original/source/model/base.obj");
    std::cout << "Model loaded: " << mycoolModel.meshes.size()
              << " mesh(es), " << mycoolModel.textures_loaded.size()
              << " material texture(s)" << std::endl;



    ModelShader.use();
    ModelShader.setInt("texture_diffuse1", 0);

    

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        fpsCounter.update();

        if (shaderMenu.update(window))
            mouse.firstMouse = true; // no view snap when the cursor is captured again

        if (!shaderMenu.menuMode)
            camera.move(window);
        // BG
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        

        ModelShader.use();
        ModelShader.setVec3("viewPos", camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
        shaderMenu.apply(ModelShader);

        ModelShader.setVec3("spotLight.position", camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
        ModelShader.setVec3("spotLight.direction", camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z);

        glm::mat4 view = camera.GetViewMatrix();
        ModelShader.setMat4("view", view);

        glm::mat4 proj = camera.perspective(screen_w, screen_h);
        ModelShader.setMat4("proj", proj);


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ModelShader.setMat4("model", model);
        glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
        mycoolModel.Draw(ModelShader);

        vertexArray.bindVAO();



        cubelightshader.use();

        cubelightshader.setMat4("view", view);

        cubelightshader.setMat4("proj", proj);
        
        glBindVertexArray(lightVAO);
        for (int i = 0; i < 1; i++){
          glm::mat4 model = glm::mat4(1.0f);
          model = glm::translate(model, shaderMenu.point_position);
         model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 5.0f));
         model = glm::scale(model, glm::vec3(0.2f));
          cubelightshader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36); }

       // camera.cords();

        fpsCounter.draw();
        shaderMenu.draw();

        ImGui::Render();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // scene draws in GL_LINE
        glDisable(GL_DEPTH_TEST);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glEnable(GL_DEPTH_TEST);

        // window
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
void frame_buffer_callback(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (shaderMenu.menuMode)
        return; // cursor is free for ImGui
    mouse.mouse_callback(window, xpos, ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (shaderMenu.menuMode)
        return; // cursor is free for ImGui
    mouse.scroll_callback(window, xoffset, yoffset);
}