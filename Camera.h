#pragma once

#include "Input.h"

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Creatio
{
	class Camera {
	private:

		int width;
		int height;
		float fov;

		glm::mat4 projection;
		glm::mat4 view;

		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;

		float yaw;
		float pitch;
		float sensibility;

		float speed;
		float deltaSpeed;

		void updateFront();
		void updateCamMouse(float offyw, float offptch);
		void init();

	public:
		Camera(int width, int height);
		Camera(int width, int height, float fov);
		//Camera(int width, int);

		//getter
		inline glm::mat4 getView() { return view; }
		inline glm::mat4 getProj() { return projection; }
		inline glm::vec3 getUp() { return up; }
		inline glm::vec3 getFront() { return front; }
		inline glm::vec3 getPos() { return position; }
		inline float getSpeed() { return speed; }
		inline float getDeltaSpeed() { return deltaSpeed; }
		inline float getYaw() { return yaw; }

		// setter
		void setFov(float fov);
		inline void setPosition(glm::vec3 pos) { position = pos; }

		//miam miam c'est bon les pitchs
		inline float getPitch() { return pitch; } 

		//setter
		inline void setView(glm::mat4 newView) { view = newView; }
		inline void setSpeed(float spd) { speed = spd; }
		inline void setDeltaSpeed(float dspd) { deltaSpeed = dspd; }
		inline void setYaw(float yw) { yaw = yw; }
		void setPitch(float ptch);
		inline void setFront(glm::vec3 frnt) { front = frnt; }

		//function
		void update();
	};
}