#ifndef RAYCASTER_MAP_EDITOR_RENDERER_HPP
#define RAYCASTER_MAP_EDITOR_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <ray.hpp>

#include <vector>

class Renderer {
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

public:
    Renderer() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    };

    void draw(Ray& ray);
};

#endif