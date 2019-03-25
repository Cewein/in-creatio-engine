#pragma once
class Object3D
{
private:
	size_t VOA;
	size_t VBO;


public:

	Object3D();

	//getter

	inline size_t getVOA() { return VOA; }
	inline size_t getVBO() { return VBO; }
	~Object3D();
};

