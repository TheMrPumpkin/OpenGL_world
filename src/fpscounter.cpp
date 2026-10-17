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
#include "shader_debug.h"
#include "fpscounter.h"

Fps_counter::Fps_counter() {
    counter = 0;
    current_fps = 0;
    prevTime = glfwGetTime();  
}

void Fps_counter::update() 
{
    crntTime = glfwGetTime(); 
    timeDiff = crntTime - prevTime;
    
    counter++;

    if (timeDiff >= 1.0) 
    {
        current_fps = counter; 
        
        counter = 0;           
        prevTime = crntTime;   
    }
}
