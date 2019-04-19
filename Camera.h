#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class Camera {
private:
	glm::mat4 projection;
	glm::mat4 view;

	glm::uvec3 position;
	glm::vec3 front;
	glm::vec3 up;

	float speed;

public:
	glm::vec3 pos;
	Camera(int width, int height);

	//getter
	inline glm::mat4 getView() { return view; }
	inline glm::mat4 getProj() { return projection; }
	inline glm::vec3 getUp() { return up; }
	inline glm::vec3 getFront() { return front; }
	inline glm::vec3 getPos() { return pos; }
	inline float getSpeed() { return speed; }

	//setter
	inline void setView(glm::mat4 newView) { view = newView; }
	inline void setSpeed(float spd) { speed = spd; }

	//adder
	inline void addPos(glm::vec3 vec) { position += vec; }
};