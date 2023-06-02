#ifndef RAYCASTER_MAP_EDITOR_MATERIAL_HPP
#define RAYCASTER_MAP_EDITOR_MATERIAL_HPP

#include <glm/vec3.hpp>

#include <shader.hpp>

struct Material {
    glm::vec3 color;
    Shader shader;

    Material() = default;

    Material(const Shader& s) {
        color = glm::vec3(1.0f);
        shader = s;
    };

    Material(const Shader& s, const glm::vec3& c) {
        color = c;
        shader = s;
    }
};

#endif