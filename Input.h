#pragma once
#include "window.h"

class Input
{

private:
	Window source;
	int mouseX;
	int mouseY;


public:
	Input(Window s);

	void processKeyboardInput();
	void processMouseInput();
	void pollEvent();


	//getter and setter
	inline int getMouseX() { return mouseX; }
	inline int getMouseY() { return mouseY; }
	

	~Input();
};

