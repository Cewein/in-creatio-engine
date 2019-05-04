#pragma once
#ifndef WINDOWH
#define WINDOWH
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

using std::cout;

class Window
{
private:
	//openGl context
	short minContext;
	short majContext;

	//windows info
	int width;
	int height;
	char * winName;

	double pastTime = 0;
	double actualTime;
	double deltaTime;

public:

	//public info
	bool isFullScreen;
	GLFWwindow * display;

	//constuctor
	Window() {}
	Window(char const * winName, short maj, short min, int w, int l, bool iFL);

	//void input();
	inline double getTime() { return glfwGetTime(); }
	void setDeltaTime();
	inline double getDeltaTime() { return deltaTime; };

	
	//getters and setters, they are inline because they are small function
	inline short getMinContext() { return this->minContext; }
	inline short getMajContext() { return this->majContext; }
	inline int getWidth() { return this->width; }
	inline int getHeight() { return this->height; }
	inline char * getName() { return this->winName; }

	inline void setName(char * newName) { this->winName = newName; }
};


#endif // !window


