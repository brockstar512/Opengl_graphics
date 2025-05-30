#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

Shader* Shader::Instance()
{
    static Shader shaderObject;
    return &shaderObject;
}

Shader::Shader()
    : m_shaderProgramID(0), m_vertexShaderID(0), m_fragmentShaderID(0) {
}

bool Shader::CreateProgram()
{
    m_shaderProgramID = glCreateProgram();
    if (m_shaderProgramID == 0) {
        std::cerr << "Error creating shader program" << std::endl;
        return false;
    }
    return true;
}

bool Shader::CreateShaders()
{
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    if (m_vertexShaderID == 0 || m_fragmentShaderID == 0) {
        std::cerr << "Error creating shaders" << std::endl;
        return false;
    }

    return true;
}

bool Shader::CompileShaders(const std::string& filename, ShaderType shaderType)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening shader file: " << filename << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();
    const GLchar* finalSourceCode = sourceCode.c_str();

    GLuint shaderID = (shaderType == ShaderType::VERTEX_SHADER)
        ? m_vertexShaderID
        : m_fragmentShaderID;

    glShaderSource(shaderID, 1, &finalSourceCode, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar errorLog[512];
        glGetShaderInfoLog(shaderID, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Shader compilation failed (" << filename << "):\n" << errorLog << std::endl;
        return false;
    }

    std::cout << "Compiled shader: " << filename << std::endl;
    return true;
}

void Shader::AttachShaders()
{
    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
}

bool Shader::LinkProgram()
{
    glLinkProgram(m_shaderProgramID);

    GLint success;
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar errorLog[512];
        glGetProgramInfoLog(m_shaderProgramID, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "Shader linking failed:\n" << errorLog << std::endl;
        return false;
    }

    glUseProgram(m_shaderProgramID);
    std::cout << "Shader program linked successfully." << std::endl;

    // Optional: validate
    glValidateProgram(m_shaderProgramID);
    GLint validated;
    glGetProgramiv(m_shaderProgramID, GL_VALIDATE_STATUS, &validated);
    if (validated == GL_FALSE) {
        GLchar validateLog[512];
        glGetProgramInfoLog(m_shaderProgramID, sizeof(validateLog), nullptr, validateLog);
        std::cerr << "Shader program validation failed:\n" << validateLog << std::endl;
        return false;
    }

    return true;
}

void Shader::DetachShaders()
{
    glDetachShader(m_shaderProgramID, m_vertexShaderID);
    glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
    m_vertexShaderID = 0;
    m_fragmentShaderID = 0;
}

void Shader::DestroyProgram()
{
    glDeleteProgram(m_shaderProgramID);
    m_shaderProgramID = 0;
}

bool Shader::SendUniformData(const std::string& uniformName, GLint data)
{
    GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (ID == -1)
    {
        std::cout << "Shader variable"<< uniformName<< " not used or found." << std::endl;
        return false;
    }
    glUniform1i(ID, data);
    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLuint data)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (ID == -1)
	{
		std::cout << "Shader variable" << uniformName << " not used or found." << std::endl;
		return false;
	}
	glUniform1ui(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat data)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (ID == -1)
	{
		std::cout << "Shader variable" << uniformName << " not used or found." << std::endl;
		return false;
	}
	glUniform1f(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (ID == -1)
	{
		std::cout << "Shader variable" << uniformName << " not used or found." << std::endl;
		return false;
	}
	glUniform2f(ID, x,y);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (ID == -1)
	{
		std::cout << "Shader variable" << uniformName << " not used or found." << std::endl;
		return false;
	}
	glUniform3f(ID, x,y,z);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, const glm::mat4& data)
{
	GLint ID = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
	if (ID == -1)
	{
		std::cout << "Shader variable" << uniformName << " not used or found." << std::endl;
		return false;
	}
	glUniformMatrix4fv(ID, 1, GL_FALSE, &data[0][0]);

	return true;

}
