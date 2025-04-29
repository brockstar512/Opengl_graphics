#pragma once
class Input
{

private:
	char m_keyUp;
	char m_keyDown;
	bool m_isXClicked;
	bool m_isKeyPressed;
	bool m_isLeftButtonClicked;
	bool m_isRightButtonClicked;
	bool m_isMiddleButtonClicked;
	int m_mouseMotionX;
	int m_mouseMotionY;
	int m_mousePositionX;
	int m_mousePositionY;



private:
	Input();
	Input(const Input&);
	Input& operator=(const Input&);

public:
	static Input* Instance();
	void Update();
	bool IsXClicked();
	bool IsKeyPressed();
	char GetKeyUp();
	char GetKeyDown();
	bool IsLeftButtonClicked();
	bool IsRightButtonClicked();
	bool IsMiddleButtonClicked();
	int GetMousePositionX();
	int GetMousePositionY();
	int GetMouseMotionX();
	int GetMouseMotionY();

};

