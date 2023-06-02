#ifndef RAYCASTER_MAP_EDITOR_TRANSFORM_HPP
#define RAYCASTER_MAP_EDITOR_TRANSFORM_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform() {
        position = glm::vec3(0.0f);
        rotation = glm::vec3(0.0f);
        scale = glm::vec3(1.0f);
    };

    Transform(const glm::vec3& position) {
        this->position = position;
        rotation = glm::vec3(0.0f);
        scale = glm::vec3(1.0f);
    }

    Transform(const glm::vec3& position, const glm::vec3& rotation) {
        this->position = position;
        this->rotation = rotation;
        scale = glm::vec3(1.0f);
    }

    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    glm::mat4 model() const {
        glm::mat4 model;
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
        model = glm::scale(model, scale);
        return model;
    }
};

#endif