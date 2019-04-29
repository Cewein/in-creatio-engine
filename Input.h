#pragma once
#include "window.h"
#include "Camera.h"
#include <vector>

class Input
{

private:
	Window source;

	float sensivity;

	float xoffset;
	float yoffset;
	float lastX;
	float lastY;

	int mouseX;
	int mouseY;


public:
	Input(Window s);

	void processKeyboardInput(Camera *cam);
	void processMouseInput(Camera *cam);
	void pollEvent(Camera *cam);


	//getter and setter
	inline int getMouseX() { return mouseX; }
	inline int getMouseY() { return mouseY; }
	

	~Input();
};

