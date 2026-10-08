#ifndef MESH_CLASS_H
#define MESH_CLASS_H
#include "glm/ext/vector_float3.hpp"
#include "shader_debug.h"
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>



struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

};
struct Texture{
    unsigned int id;
    std::string type;
};


class Mesh
{

public:
// mash data
std::vector<Vertex>     vertices;
std::vector<unsigned int> include;
std::vector<Texture> textures;

Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> include  , std::vector<Texture> textures){
    this-> vertices = vertices;
    this-> include = include;
    this-> textures = textures;

    setupMesh();
}

// all the texture and how much i want !
void Draw(Shader &Shader){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0  + i);
    std::string number;
    std::string name = textures[i].type;
    if (name == "texture_diffuse") {
    number = std::to_string(diffuseNr++);
    }
    else if (name == "texture_specular") {
    number = std::to_string(specularNr++);
    }
    Shader.setInt(("material." + name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D , textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES , include.size() , GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}


private:
// ## render data
unsigned int VAO , VBO , EBO;
void setupMesh(){

    // all the buffers !!!
    glGenVertexArrays(1 , &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER , VBO);
    glBufferData(GL_ARRAY_BUFFER , vertices.size() * sizeof(Vertex) , &vertices[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER  , include.size() * sizeof(unsigned int) , &include[0],GL_STATIC_DRAW);

    // pos 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , sizeof(Vertex) , (void*)0);


    // normal 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3 , GL_FLOAT , GL_FALSE , sizeof(Vertex) , (void*)offsetof(Vertex, Normal));
    // UV or texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2 , GL_FLOAT , GL_FALSE , sizeof(Vertex) , (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);




}


    

};



#endif