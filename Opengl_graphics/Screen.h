#pragma once
#include <SDL3/SDL.h>// i tried using #include <SDL.h>, but it would not work have SLD3 in the properties vc++ lib path bc all the other header files have inclide SDL3/*** already in them so it was breaking it.
class Screen {
public:
	bool Initialize();
	void Clear();
	void Render();
	void Destroy();

private:
	Screen();
	Screen(const Screen&);
	//cannot assign one screen to another... this willl be a singleton
	Screen& operator=(const Screen&);

public:
	static Screen* Instance();

private:
	SDL_Window* window;//window
	SDL_GLContext context;//canvas that the window renders 
};
