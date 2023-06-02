#include <renderer.hpp>

void Renderer::draw(Ray& ray) {
    ray.setup();
    vertices = ray.vertices;
    indices = ray.indices;

    unsigned int numIndices = indices.size();
    size_t verticesByteSize = vertices.size() * sizeof(float);
    size_t indicesByteSize = numIndices * sizeof(unsigned int);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesByteSize, vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices.data(), GL_STATIC_DRAW);

    // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup model matrix and shader uniform values
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, ray.origin - ray.transform.position);
    model = glm::rotate(model, glm::radians(ray.transform.rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::scale(model, ray.transform.scale);
    ray.material.shader.set("model", model);
    ray.material.shader.set("color", ray.material.color);

    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
}