#include "shader.hpp"
#include <imgui.h>


void Shader::checkCompileErrors(unsigned int program)
{
    GLint linkStatus;

    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        GLchar message[1024];
        glGetProgramInfoLog(program, IM_ARRAYSIZE(message), nullptr, message);
        printf("Program link error : %s", message);
    }
}

GLuint Shader::createShader(GLenum type, int sourceCount, const char** sources)
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
        printf("Saherd compilation error : %s", message);
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
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
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
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
 
    vertex = createShader(GL_VERTEX_SHADER, 1, &vShaderCode);
    fragment = createShader(GL_FRAGMENT_SHADER, 1, &fShaderCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}



void Shader::use() 
{ 
    glUseProgram(ID); 
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void Shader::setMat4(const std::string &name, const Mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

