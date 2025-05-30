#pragma once

#include <string>
#include "glad.h"
#include <glm.hpp>



class Shader {
public:
    enum class ShaderType {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };
    static Shader* Instance();

    bool CreateProgram();
    bool CreateShaders();
    bool CompileShaders(const std::string& filename, ShaderType shaderType);
    void AttachShaders();
    bool LinkProgram();
    void DetachShaders();
    void DestroyShaders();
    void DestroyProgram();
    GLuint GetShaderProgramID() const { return m_shaderProgramID; }
    bool SendUniformData(const std::string& uniformName, GLint data);
	bool SendUniformData(const std::string& uniformName, GLuint data);
	bool SendUniformData(const std::string& uniformName, GLfloat data);
	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y);
	bool SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z);
	bool SendUniformData(const std::string& uniformName, const glm::mat4& data);





private:
    Shader(); // Private constructor for singleton pattern
    GLuint m_shaderProgramID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};
