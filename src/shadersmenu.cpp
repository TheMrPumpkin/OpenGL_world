#include "shadersmenu.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

void Shaders_menu::draw()
{
    ImGui::Begin("Shaders");
    ImGui::SliderFloat("Shininess", &shininess, 1.0f, 256.0f);

    if (ImGui::CollapsingHeader("Directional light", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::DragFloat3("Direction", glm::value_ptr(dir_direction), 0.01f);
        ImGui::ColorEdit3("Ambient##dir", glm::value_ptr(dir_ambient));
        ImGui::ColorEdit3("Diffuse##dir", glm::value_ptr(dir_diffuse));
        ImGui::ColorEdit3("Specular##dir", glm::value_ptr(dir_specular));
    }

    if (ImGui::CollapsingHeader("Point light", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::DragFloat3("Position##point", glm::value_ptr(point_position), 0.01f);
        ImGui::ColorEdit3("Ambient##point", glm::value_ptr(point_ambient));
        ImGui::ColorEdit3("Diffuse##point", glm::value_ptr(point_diffuse));
        ImGui::ColorEdit3("Specular##point", glm::value_ptr(point_specular));
        ImGui::DragFloat("Constant", &point_constant, 0.001f, 0.0f, 10.0f);
        ImGui::DragFloat("Linear", &point_linear, 0.001f, 0.0f, 10.0f);
        ImGui::DragFloat("Quadratic", &point_quadratic, 0.001f, 0.0f, 10.0f);
    }

    if (ImGui::CollapsingHeader("Spot light", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::ColorEdit3("Ambient##spot", glm::value_ptr(spot_ambient));
        ImGui::ColorEdit3("Diffuse##spot", glm::value_ptr(spot_diffuse));
        ImGui::ColorEdit3("Specular##spot", glm::value_ptr(spot_specular));
        ImGui::DragFloat("Constant##spot", &spot_constant, 0.001f, 0.0f, 10.0f);
        ImGui::DragFloat("Linear##spot", &spot_linear, 0.001f, 0.0f, 10.0f);
        ImGui::DragFloat("Quadratic##spot", &spot_quadratic, 0.001f, 0.0f, 10.0f);
        ImGui::SliderFloat("Cutoff (deg)", &spot_cutoff_deg, 0.0f, 90.0f);
        ImGui::SliderFloat("Outer cutoff (deg)", &spot_outercutoff_deg, 0.0f, 90.0f);
        if (spot_outercutoff_deg < spot_cutoff_deg)
            spot_outercutoff_deg = spot_cutoff_deg;
    }

    if (ImGui::Button("Reset to defaults"))
        reset();

    ImGui::End();
}

void Shaders_menu::reset()
{
    bool mode = menuMode, held = escHeld;
    *this = Shaders_menu{};
    menuMode = mode;
    escHeld = held;
}

bool Shaders_menu::update(GLFWwindow *window)
{
    bool escNow = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
    bool changed = escNow && !escHeld;
    escHeld = escNow;
    if (!changed)
        return false;

    menuMode = !menuMode;
    glfwSetInputMode(window, GLFW_CURSOR, menuMode ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    return true;
}

void Shaders_menu::apply(Shader &shader) const
{
    shader.setFloat("material.shininess", shininess);

    shader.setVec3("dirLight.direction", dir_direction.x, dir_direction.y, dir_direction.z);
    shader.setVec3("dirLight.ambient", dir_ambient.x, dir_ambient.y, dir_ambient.z);
    shader.setVec3("dirLight.diffuse", dir_diffuse.x, dir_diffuse.y, dir_diffuse.z);
    shader.setVec3("dirLight.specular", dir_specular.x, dir_specular.y, dir_specular.z);

    shader.setVec3("pointLights[0].position", point_position.x, point_position.y, point_position.z);
    shader.setVec3("pointLights[0].ambient", point_ambient.x, point_ambient.y, point_ambient.z);
    shader.setVec3("pointLights[0].diffuse", point_diffuse.x, point_diffuse.y, point_diffuse.z);
    shader.setVec3("pointLights[0].specular", point_specular.x, point_specular.y, point_specular.z);
    shader.setFloat("pointLights[0].constant", point_constant);
    shader.setFloat("pointLights[0].linear", point_linear);
    shader.setFloat("pointLights[0].quadratic", point_quadratic);

    shader.setVec3("spotLight.ambient", spot_ambient.x, spot_ambient.y, spot_ambient.z);
    shader.setVec3("spotLight.diffuse", spot_diffuse.x, spot_diffuse.y, spot_diffuse.z);
    shader.setVec3("spotLight.specular", spot_specular.x, spot_specular.y, spot_specular.z);
    shader.setFloat("spotLight.constant", spot_constant);
    shader.setFloat("spotLight.linear", spot_linear);
    shader.setFloat("spotLight.quadratic", spot_quadratic);
    shader.setFloat("spotLight.cutoff", glm::cos(glm::radians(spot_cutoff_deg)));
    shader.setFloat("spotLight.outercutoff", glm::cos(glm::radians(spot_outercutoff_deg)));
}
