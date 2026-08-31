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

class Texture2D
{
private:
    int w, h, nchanel;

public:
    GLuint ID;
    unsigned char *data;
    Texture2D(const char *imagepath);
    void bind();
};
