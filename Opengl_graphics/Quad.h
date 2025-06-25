#pragma once
#include "gl.h"
#include "Buffer.h"
#include <glm.hpp>
#include "Texture.h"

class Quad
{
public: 
	Quad();
	~Quad();
	void Render();
	void Update();

private:
	Buffer m_buffer;
	Texture m_texture;
	glm::mat4 m_model;

	float m_shininess;
	glm::vec3 m_position;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

