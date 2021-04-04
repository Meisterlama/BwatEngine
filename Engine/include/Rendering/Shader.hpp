#pragma once

#include <string>
#include "Math/Math.hpp"
#include "glad/glad.h"

namespace Rendering
{
    class Shader
    {
    private:

        void checkCompileErrors(unsigned int shader);

    public:

        // the program ID
        unsigned int ID;

        // constructor 
        Shader() {};
        ~Shader() {}; // rule of three -> https://en.cppreference.com/w/cpp/language/rule_of_three
        Shader(const char* vertexPath, const char* fragmentPath);

        //create Shader
        GLuint createShader(GLenum type, int sourceCount, const char** sources);

        // use/activate the shader
        void use();

        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setMat4(const std::string &name, const BwatEngine::Math::Mat4f &mat) const;
        

    };
}
