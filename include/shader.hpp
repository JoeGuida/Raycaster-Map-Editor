#ifndef RAYCASTER_MAP_EDITOR_SHADER_HPP
#define RAYCASTER_MAP_EDITOR_SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
    unsigned int ID;

    Shader() = default;
    Shader (const std::string& shaderPath, const std::string& vertexPath, const std::string& fragmentPath);
    void set(const char* uniformName, float value) const;
    void set(const char* uniformName, int value) const;
    void set(const char* uniformName, const glm::mat4& value) const;
    void set(const char* uniformName, const glm::vec3& value) const;
    void set(const char* uniformName, float x, float y, float z) const;
    void use() const;
};

#endif