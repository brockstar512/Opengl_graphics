#include "Light.h"
#include "Shader.h"
#include "input.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>

Light::Light()
{
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f, -0.25f, -1.5f);
	//(0, -0.5, -1.5)
	GLfloat vertices[] = { 0.0f,0.0f,0.0f };
	GLfloat colors[] = { 1.0f,1.0f,1.0f };
	m_buffer.CreateBuffer(1);
	m_buffer.FillVBO(Buffer::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::SINGLE);
	m_buffer.FillVBO(Buffer::COLOR_BUFFER, colors, sizeof(colors), Buffer::SINGLE);

	m_buffer.LinkBuffer("vertexIn", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	m_buffer.LinkBuffer("colorIn", Buffer::COLOR_BUFFER, Buffer::RGB, Buffer::FLOAT);

}

Light::~Light()
{
	m_buffer.DestroyBuffer();
}

void Light::Update()
{
	if (Input::Instance()->IsKeyPressed()) {
		//left
		if (Input::Instance()->GetKeyDown() == 'j')
		{
			m_position.x -= .01f;
		}
		else if (Input::Instance()->GetKeyDown() == 'k')
		{
			m_position.z += .01f;

		}
		//up
		else if (Input::Instance()->GetKeyDown() == 'u')
		{
			m_position.y += .01f;

		}
		//down
		else if (Input::Instance()->GetKeyDown() == 'o')
		{
			m_position.y -= .01f;

		}
		else if (Input::Instance()->GetKeyDown() == 'i')
		{
			m_position.z -= .01f;

		}
		//right
		else if (Input::Instance()->GetKeyDown() == 'l')
		{
			m_position.x += .01f;

		}

	}
	//std::cout << "light location: ("
	//	<< m_position.x << ", "
	//	<< m_position.y << ", "
	//	<< m_position.z << ")" << std::endl;	
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
}

void Light::Render()
{
	Shader::Instance()->SendUniformData("model", m_model);
	Shader::Instance()->SendUniformData("isLit", false);
	Shader::Instance()->SendUniformData("isTextured", false);

	glPointSize(20.0f);
	m_buffer.Render(Buffer::POINTS);
}

void Light::SendToShader()
{
	Shader::Instance()->SendUniformData("light.position", m_position.r, m_position.g, m_position.b);
	Shader::Instance()->SendUniformData("light.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	Shader::Instance()->SendUniformData("light.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	Shader::Instance()->SendUniformData("light.specular", m_specular.r, m_specular.g, m_specular.b);

}
