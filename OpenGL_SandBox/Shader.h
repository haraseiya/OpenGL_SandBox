#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);


    void Use();

    void SetValue(const std::string& name, bool value) const;
    void SetValue(const std::string& name, int value) const;
    void SetValue(const std::string& name, float value) const;
    void SetValue(const std::string& name, glm::mat4& value) const;

private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};