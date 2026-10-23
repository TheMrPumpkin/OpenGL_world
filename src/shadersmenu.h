#ifndef SHADERSMENU_H
#define SHADERSMENU_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_debug.h"
#include <GLFW/glfw3.h>

class Shaders_menu {
public:
    bool menuMode = false; // cursor free + camera frozen

    float shininess = 64.0f;

    glm::vec3 dir_direction{-2.0f, 0.5f, 1.0f};
    glm::vec3 dir_ambient{0.1f};
    glm::vec3 dir_diffuse{0.5f};
    glm::vec3 dir_specular{1.0f};

    glm::vec3 point_position{2.0f, 0.0f, 0.0f};
    glm::vec3 point_ambient{0.1f};
    glm::vec3 point_diffuse{0.5f};
    glm::vec3 point_specular{1.0f};
    float point_constant = 1.0f;
    float point_linear = 0.09f;
    float point_quadratic = 0.032f;

    glm::vec3 spot_ambient{0.1f};
    glm::vec3 spot_diffuse{0.5f};
    glm::vec3 spot_specular{1.0f};
    float spot_constant = 1.0f;
    float spot_linear = 0.09f;
    float spot_quadratic = 0.032f;
    float spot_cutoff_deg = 40.0f;
    float spot_outercutoff_deg = 50.0f;

    void draw();
    void apply(Shader &shader) const;
    void reset();
    bool update(GLFWwindow *window); // true when ESC changed the mode

private:
    bool escHeld = false;
};

#endif
