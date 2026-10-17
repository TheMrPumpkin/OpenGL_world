#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H
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




class Fps_counter {
private:
    GLuint id;               
    unsigned int counter; 
    unsigned int current_fps;   
    double last_time;  
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff; 

public:
    Fps_counter();   
    
    void update();          
    unsigned int get_fps() const { return current_fps; }
};

#endif

