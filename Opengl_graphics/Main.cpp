#include <iostream>
#include "Screen.h"
#include "Input.h"
#include "glad.h"


bool isAppRunning = true;

int main(int argc, char* argv[])
{
	Screen::Instance()->Initialize();


	while (isAppRunning)
	{
		Screen::Instance()->Clear();
		Input::Instance()->Update();

		char keyPressed = Input::Instance()->GetKeyDown();
	
		
		//update/render
		Screen::Instance()->Render();


		isAppRunning = !Input::Instance()->IsXClicked();
	}

	Screen::Instance()->Destroy();

	return 0;
}

