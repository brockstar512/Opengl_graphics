#include "Buffer.h"
#include "Shader.h"

Buffer::Buffer()
{
	 m_VAO = 0;
	 m_vertexVBO = 0;
	 m_colorVBO = 0;
	 m_totalVertices = 0;
	 m_textureVBO = 0;
}

void Buffer::CreateBuffer(GLuint totalVertices)
{
	// 1) create the buffer
	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenVertexArrays(1, &m_VAO);
	m_totalVertices = totalVertices;

}

void Buffer::FillVBO(VBOType vboType, GLfloat* data, GLsizeiptr bufferSize, FillType fillType)
{
	glBindVertexArray(m_VAO);
	if (vboType == VBOType::VERTEX_BUFFER) {
		//2) bind the buffer so we can used it
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
	}
	else if (vboType == VBOType::COLOR_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);

	}
	//3) give it the data
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, static_cast<GLenum>(fillType));
	//4) we are not using it anymore
	glBindVertexArray(0);

}

void Buffer::FillEBO(GLuint* data, GLsizeiptr bufferSize, FillType fillType)
{
}

void Buffer::LinkBuffer(const std::string& attribute, VBOType vboType, ComponentType componentType, DataType dataType)
{
	GLuint shaderProgramId = Shader::Instance()->GetShaderProgramID();

	//get the id of the attribute variable in the shader so we can write to it
	GLint Id = glGetAttribLocation(shaderProgramId, attribute.c_str());
	
	//Binds the VAO that�s part of the Buffer class. All buffer / attribute state set next will be stored in this VAO.	
	glBindVertexArray(m_VAO); 

	//choose which buffer to bind to
	if (vboType == VBOType::VERTEX_BUFFER) {

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
	}
	else if (vboType == VBOType::COLOR_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);

	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);

	}
	//Describes how to interpret the buffer's data for the shader attribute:
	glVertexAttribPointer(Id, static_cast<GLint>(componentType), GL_FLOAT, GL_FALSE, 0, nullptr);
	//Enables this attribute for use in rendering.
	glEnableVertexAttribArray(Id);
	glBindVertexArray(0);

}

void Buffer::Render(DrawType drawType)
{
	glBindVertexArray(m_VAO);
	glDrawArrays(static_cast<GLenum>(drawType), 0, m_totalVertices);
	glBindVertexArray(0);
}

void Buffer::DestroyBuffer()
{
	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteBuffers(1, &m_colorVBO);
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteVertexArrays(1, &m_VAO);
}


