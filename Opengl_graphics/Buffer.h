#pragma once
#include "gl.h"
#include <string>
class Buffer
{
public:
	//adding class to enum is a more modern way of delcaring enums to ensure that the enums belongs to these types of classes
	enum class VBOType { 
		VERTEX_BUFFER, 
		COLOR_BUFFER, 
		TEXTURE_BUFFER };
	enum class ComponentType { 
		XY = 2, 
		XYZ = 3, 
		RGB = 3, 
		RGBA = 4, 
		UV = 2 };
	enum class FillType {
		ONCE = GL_STATIC_DRAW, 
		ONGOING = GL_DYNAMIC_DRAW};
	enum class DataType {
		INT = GL_INT, 
		FLOAT = GL_FLOAT, 
		UNSIGNED_INT = GL_UNSIGNED_INT};
	enum class DrawType{
		POINTS = GL_POINTS, 
		TRIANGLES = GL_TRIANGLES,
		LINES = GL_LINES};
	Buffer();
	void CreateBuffer(GLuint totalVertices);
	void FillVBO(VBOType vboType, GLfloat* data, GLsizeiptr bufferSize, FillType fillType);
	void FillEBO(GLuint* data, GLsizeiptr bufferSize, FillType fillType);
	void LinkBuffer(const std::string& attribute, VBOType vboType, ComponentType componentType, DataType dataType);
	void Render(DrawType drawType);
	void DestroyBuffer();

private:
	GLuint m_VAO;
	GLuint m_vertexVBO;
	GLuint m_colorVBO;
	GLuint m_totalVertices;
	GLuint m_textureVBO;

};

