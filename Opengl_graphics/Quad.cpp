#include <gtc/matrix_transform.hpp>
#include "Quad.h"
#include "Shader.h"
#include "Input.h"

Quad::Quad()
{
	GLfloat vertices[] = {
		// Position       
		-0.5f, 0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f,
		 -0.5f,  -0.5f, 0.0f,

		-0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
	};
	//GLfloat rainbocolors[] = {

	//	 1.0f, 0.0f, 0.0f,
	//	 0.0f, 0.0f, 1.0f,
	//	 0.0f, 1.0f, 1.0f,

	//	 0.0f, 1.0f, 1.0f ,
	//	 0.0f, 0.0f, 1.0f,
	//	 0.0f, 1.0f, 0.0f,
	//};
	GLfloat colors[] = {

			 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,

			 1.0f, 1.0f, 1.0f ,
			 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f,
		};

	GLfloat UVs[] = {
		0.0f,1.0f,
		1.0f,1.0f,
		0.0f,0.0f,

		0.0f,0.0f,
		1.0f,1.0f,
		1.0f,0.0f
	};

	m_buffer.CreateBuffer(6);
	m_buffer.FillVBO(Buffer::VERTEXT_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);
	m_buffer.FillVBO(Buffer::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::SINGLE);

	m_buffer.LinkBuffer("vertexIn", Buffer::VERTEXT_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);
	m_buffer.LinkBuffer("textureIn", Buffer::TEXTURE_BUFFER, Buffer::UV, Buffer::FLOAT);

	m_texture.Load("Textures/crate.png");
	m_position = glm::vec3(0.0f);

}

Quad::~Quad()
{

	m_buffer.DestroyBuffer();
}

void Quad::Render()
{
	Shader::Instance()->SendUniformData("model", m_model);
	m_texture.Bind();
	m_buffer.Render(Buffer::TRIANGLES);
	m_texture.Unbind();

}

void Quad::Update()
{
	if (Input::Instance()->IsKeyPressed()) {
		if (Input::Instance()->GetKeyDown() == 'j')
		{
			m_position.x -= .01f;
		}
		else if (Input::Instance()->GetKeyDown() == 'k')
		{
			m_position.z += .01f;

		}
		else if (Input::Instance()->GetKeyDown() == 'u')
		{
			m_position.y += .01f;

		}
		else if (Input::Instance()->GetKeyDown() == 'o')
		{
			m_position.y -= .01f;

		}
		else if (Input::Instance()->GetKeyDown() == 'i')
		{
			m_position.z -= .01f;

		}
		else if (Input::Instance()->GetKeyDown() == 'l')
		{
			m_position.x += .01f;

		}

	}
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
}
