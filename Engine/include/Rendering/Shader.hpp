#pragma once

#include <string>
#include "Math/Math.hpp"
#include "glad/glad.h"

namespace Rendering
{
    class Shader
    {
    private:

        void CheckCompileErrors(unsigned int shader);

    public:

        // the program ID
        unsigned int ID;

        // constructor 
        Shader() {};
        ~Shader() {};
        Shader(const char* vertexPath, const char* fragmentPath);

        //create Shader
        GLuint CreateShader(GLenum type, int sourceCount, const char** sources);

        // use/activate the shader
        void Use();

        // utility uniform functions
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, float x, float y) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetVec4(const std::string& name, float x, float y, float z,float w) const;
        void SetMat4(const std::string &name, const BwatEngine::Math::Mat4f &mat) const;
        void SetTexture(const std::string& name, int value, int idTexture);
        void SetTextureCubemap(const std::string& name, GLuint value, GLuint idTexture);

        

    };
}