#pragma once
#include "glad.h"
#include "Buffer.h"
class Quad
{
public: 
	Quad();
	~Quad();
	void Render();
private:
	Buffer m_buffer;

};

