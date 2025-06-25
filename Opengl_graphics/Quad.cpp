#include <gtc/matrix_transform.hpp>
#include "Quad.h"
#include "Shader.h"
#include "Input.h"
#include <iostream>

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
	m_buffer.FillVBO(Buffer::VBOType::VERTEX_BUFFER, vertices, sizeof(vertices), Buffer::FillType::ONCE);
	m_buffer.FillVBO(Buffer::VBOType::COLOR_BUFFER, colors, sizeof(colors), Buffer::FillType::ONCE);
	m_buffer.FillVBO(Buffer::VBOType::TEXTURE_BUFFER, UVs, sizeof(UVs), Buffer::FillType::ONCE);

	m_buffer.LinkBuffer("vertexIn", Buffer::VBOType::VERTEX_BUFFER, Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.LinkBuffer("colorIn", Buffer::VBOType::COLOR_BUFFER, Buffer::ComponentType::RGB, Buffer::DataType::FLOAT);
	m_buffer.LinkBuffer("textureIn", Buffer::VBOType::TEXTURE_BUFFER, Buffer::ComponentType::UV, Buffer::DataType::FLOAT);

	m_texture.Load("Textures/crate.png");
	m_shininess = 50.0f;
	m_position = glm::vec3(0.0f, -0.5f, -1.5f);
	m_ambient = glm::vec3(0.4f,0.4f,0.4f);
	m_diffuse = glm::vec3(0.1f,0.7f,0.2f);
	m_specular = glm::vec3(0.8f, 0.8f, 0.8f);


}

Quad::~Quad()
{

	m_buffer.DestroyBuffer();
}

void Quad::Render()
{
	Shader::Instance()->SendUniformData("model", m_model);
	Shader::Instance()->SendUniformData("isLit", true);
	Shader::Instance()->SendUniformData("isTextured", true);

	Shader::Instance()->SendUniformData("material.shininess", m_shininess);
	Shader::Instance()->SendUniformData("material.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	Shader::Instance()->SendUniformData("material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	Shader::Instance()->SendUniformData("material.specular", m_specular.r, m_specular.g, m_specular.b);

	m_texture.Bind();
	m_buffer.Render(Buffer::DrawType::TRIANGLES);
	m_texture.Unbind();

}

void Quad::Update()
{
	//if (Input::Instance()->IsKeyPressed()) {
	//	if (Input::Instance()->GetKeyDown() == 'j')
	//	{
	//		m_position.x -= .01f;
	//	}
	//	else if (Input::Instance()->GetKeyDown() == 'k')
	//	{
	//		m_position.z += .01f;

	//	}
	//	else if (Input::Instance()->GetKeyDown() == 'u')
	//	{
	//		m_position.y += .01f;

	//	}
	//	else if (Input::Instance()->GetKeyDown() == 'o')
	//	{
	//		m_position.y -= .01f;

	//	}
	//	else if (Input::Instance()->GetKeyDown() == 'i')
	//	{
	//		m_position.z -= .01f;

	//	}
	//	else if (Input::Instance()->GetKeyDown() == 'l')
	//	{
	//		m_position.x += .01f;

	//	}

	//}
	/*std::cout << "quad location: ("
		<< m_position.x << ", "
		<< m_position.y << ", "
		<< m_position.z << ")" << std::endl;*/

	m_model = glm::translate(m_model, m_position);
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::rotate(m_model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));
}
