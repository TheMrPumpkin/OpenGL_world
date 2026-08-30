#ifndef VERTEXRRAY_CLASS_H
#define VERTEXRRAY_CLASS_H
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class VertexArray
{
private:
    GLuint ID;

public:
    GLuint VBO, VAO, EBO;
    std::vector<glm::vec3> cubePositions; // put array in class
    void cubePos(GLuint i);
    void Vertexarray();
    void bind();
};

#endif
