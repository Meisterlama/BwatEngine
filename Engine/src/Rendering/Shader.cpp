#include "Rendering/Shader.hpp"
#include <imgui.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Debug/Logger.hpp"

using namespace Rendering;

void Shader::CheckCompileErrors(unsigned int program)
{
    GLint linkStatus;

    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        GLchar message[1024];
        glGetProgramInfoLog(program, IM_ARRAYSIZE(message), nullptr, message);
        LogError("Program link error : %s", message);

    }
}

GLuint Shader::CreateShader(GLenum type, int sourceCount, const char** sources)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, sourceCount, sources, nullptr);
    glCompileShader(shader);

    //debug shader
    GLint compileshader;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileshader);

    if (compileshader == GL_FALSE)
    {
        GLchar message[1024];
        glGetShaderInfoLog(shader, IM_ARRAYSIZE(message), nullptr, message);
        LogError("Shader compilation error : %s", message);
    }

    return shader;
}


Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        
        vShaderFile.open(std::filesystem::relative(vertexPath ));
        fShaderFile.open(std::filesystem::relative(fragmentPath ));
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        LogError("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
 
    vertex = CreateShader(GL_VERTEX_SHADER, 1, &vShaderCode);
    fragment = CreateShader(GL_FRAGMENT_SHADER, 1, &fShaderCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}



void Shader::Use() 
{ 
    glUseProgram(ID); 
}

void Shader::SetBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::SetInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::SetFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::SetVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}
void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}


void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::SetMat4(const std::string &name, const BwatEngine::Math::Mat4f &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.values);
}


void Shader::SetTexture(const std::string& name, int value, int idTexture)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

    glActiveTexture(GL_TEXTURE0 + value);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    glActiveTexture(GL_TEXTURE0);
}

void Shader::SetTextureCubemap(const std::string& name, GLuint value, GLuint idTexture)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

    glActiveTexture(GL_TEXTURE0 + value);
    glBindTexture(GL_TEXTURE_CUBE_MAP, idTexture);
    glActiveTexture(GL_TEXTURE0);
}