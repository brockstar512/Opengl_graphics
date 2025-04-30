#include <iostream>
#include "Screen.h"
#include "Input.h"
#include "glad.h"
#include "Shader.h"

bool isAppRunning = true;

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
	 0.0f, 1.0f, 0.0f,

	 0.0f, 1.0f, 1.0f , 
	 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f,
};




int main(int argc, char* argv[])
{
	Screen::Instance()->Initialize();

	if (!Shader::Instance()->CreateProgram())
	{
		return 0;
	}

	if(!Shader::Instance()->CreateShaders())
	{
		return 0;
	}
	
	Shader::Instance()->CompileShaders("Shaders/Main.vert", Shader::ShaderType::VERTEX_SHADER);

	Shader::Instance()->CompileShaders("Shaders/Main.frag", Shader::ShaderType::FRAGMENT_SHADER);


	Shader::Instance()->AttachShaders();

	Shader::Instance()->LinkProgram();

	GLuint shaderProgramId = Shader::Instance()->GetShaderProgramID();
	GLint vertexId = glGetAttribLocation(shaderProgramId, "vertexIn");
	GLint colorId = glGetAttribLocation(shaderProgramId, "colorIn");

	GLuint vertexVBO;
	glGenBuffers(1, &vertexVBO);
	GLuint colorxVBO;
	glGenBuffers(1, &colorxVBO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexId, 3, GL_FLOAT, GL_FALSE,0, nullptr);
	glEnableVertexAttribArray(vertexId);

	glBindBuffer(GL_ARRAY_BUFFER, colorxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(colorId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(colorId);



	while (isAppRunning)
	{
		Screen::Instance()->Clear();
		Input::Instance()->Update();

		char keyPressed = Input::Instance()->GetKeyDown();
	
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//update/render
		Screen::Instance()->Render();


		isAppRunning = !Input::Instance()->IsXClicked();
	}

	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();

	Screen::Instance()->Destroy();

	return 0;
}

