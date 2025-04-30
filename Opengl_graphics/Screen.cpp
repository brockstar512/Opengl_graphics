#include <iostream>
#include "Screen.h"
#include "glad.h"
bool Screen::Initialize()
{
	if (!SDL_Init(
		SDL_INIT_VIDEO |
		SDL_INIT_AUDIO |
		SDL_INIT_GAMEPAD
	))
	{
		std::cout << "Erroring initializing" << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//1 indicates true, this means when rendering to the screen this will use two fram buffers... one that is displayed on the screen another that is rendered behind the scene

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	
	/*
		Core Profile (Modern OpenGL):
		Must use VAOs, VBOs, and GLSL shaders.
		Can’t use glBegin/glEnd, matrix stacks, or immediate mode rendering.
		Compatibility Profile (Legacy + Modern):
		You can use both glBegin/glEnd and shaders.
		Useful for legacy applications or educational purposes.
	*/


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	window = SDL_CreateWindow(
		"Graphics Engine",
		1280, 720,
		SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cout << "Error window initialization" << std::endl;
		return false;

	}

	context = SDL_GL_CreateContext(window);

	if (!context)
	{
		std::cout << "Error context initialization" << std::endl;
		return false;

	}

	if (!gladLoadGL())
	{
		std::cout << "Error loading glad extensions" << std::endl;
	}

	return true;
}

Screen::Screen()
{
	window = nullptr;
	context = nullptr;
}

void Screen::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::Render()
{
	SDL_GL_SwapWindow(window);
}

void Screen::Destroy()
{
	SDL_GL_DestroyContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


Screen* Screen::Instance()
{
	//with static variables. all calls will return the screen pointer 
	static Screen* screen = new Screen;
	return screen;
}
