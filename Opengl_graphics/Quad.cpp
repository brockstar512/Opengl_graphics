#include "Quad.h"
#include "Shader.h"

Quad::Quad()
{
	float vertices[] = {
		// Position       
		-0.5f, 0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f,
		 -0.5f,  -0.5f, 0.0f,

		-0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
	};
	float colors[] = {

		 1.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 1.0f,
		 0.0f, 1.0f, 1.0f,

		 0.0f, 1.0f, 1.0f ,
		 0.0f, 0.0f, 1.0f,
		 0.0f, 1.0f, 0.0f,
	};

	m_buffer.CreateBuffer(6);
	m_buffer.FillVBO(Buffer::VERTEXT_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);
	m_buffer.LinkBuffer("vertexIn", Buffer::VERTEXT_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);


}

Quad::~Quad()
{

	m_buffer.DestroyBuffer();
}

void Quad::Render()
{
	m_buffer.Render(Buffer::TRIANGLES);
}
