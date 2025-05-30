#pragma once
#include "glad.h"
#include "Buffer.h"
#include <glm.hpp>
class Quad
{
public: 
	Quad();
	~Quad();
	void Render();
	void Update();

private:
	Buffer m_buffer;
	glm::mat4 m_model;
	glm::vec3 m_position;
};

