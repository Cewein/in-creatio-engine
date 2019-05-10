#pragma once
#include "window.h"
#include "Camera.h"
#include <vector>

#define NUMBERINPUT 7

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define SHIFT 4
#define FASTER 5
#define SLOWER 6

namespace Creatio
{
	class Input
	{

	private:

		static Input *singleton; //pointer to singleton
		Input(Creatio::Window s); //private constructor
		Input(); //second private constructor

		Creatio::Window source;

		bool key[NUMBERINPUT];

		float mouseX;
		float mouseY;

		float lastX;
		int lastY;

		float xoffset;
		float yoffset;


	public:
		//Input(Window s);

		void processKeyboardInput();
		void processMouseInput();
		void pollEvent();

		//remove duplication
		Input(const Input&) = delete;
		Input& operator = (const Input&) = delete;

		//get the singleton, if you have not init please do or it will not work
		static Input *get()
		{
			if (!singleton)
			{
				exit(2);
			}
			return singleton;
		}

		//this must be the first one for link the windows and the input
		static Input *init(Creatio::Window s)
		{
			if (!singleton)
			{
				singleton = new Input(s);
			
			}
			return singleton;
		}


		//getter and setter
		float getmouseX(); 
		float getmouseY(); 
		float getOffsetY(); 
		float getOffsetX(); 
	
		int getkey(int i); 
		double getDeltaTime();

	};
}

