#pragma once

#include <glm.hpp>
#include "glad.h"
class Camera
{
public:
	Camera();
	void Update();
	void Set3DView();

protected:
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::vec3 m_up;
	glm::vec3 m_position;
	glm::vec3 m_direction;

};

