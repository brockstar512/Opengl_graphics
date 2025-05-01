#include <iostream>
#include "Screen.h"
#include "Input.h"
#include "glad.h"
#include "Shader.h"
#include "Quad.h"

bool isAppRunning = true;



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

	Quad quad;


	while (isAppRunning)
	{
		Screen::Instance()->Clear();
		Input::Instance()->Update();

		char keyPressed = Input::Instance()->GetKeyDown();
	

		quad.Render();

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

