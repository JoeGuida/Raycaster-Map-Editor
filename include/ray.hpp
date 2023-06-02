#ifndef RAYCASTER_MAP_EDITOR_RAY_HPP
#define RAYCASTER_MAP_EDITOR_RAY_HPP

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <material.hpp>
#include <transform.hpp>

#include <vector>

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
    float distance;

    Material material;
    Transform transform;
    std::vector<unsigned int> indices = {0, 1};
    std::vector<float> vertices;

    Ray() {
        origin = glm::vec3(0.0f);
        direction = glm::vec3(0.0f, -1.0f, 0.0f);
        distance = 1000.0f;
    }

    Ray(const glm::vec3& o, const glm::vec3& d) {
        origin = o;
        direction = glm::normalize(d);
        distance = 1000.0f;
    }

    void setMaterial(const Material& m);
    void setTransform(const Transform& t);
    void setup();
};

#endif
