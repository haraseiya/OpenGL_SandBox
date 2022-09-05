#pragma once

#include <glad/glad.h>

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

    // activate the shader
    // ------------------------------------------------------------------------
    void Use();

    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetValue(const std::string& name, bool value) const;

    // ------------------------------------------------------------------------
    void SetValue(const std::string& name, int value) const;

    // ------------------------------------------------------------------------
    void SetValue(const std::string& name, float value) const;

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(unsigned int shader, std::string type);
};