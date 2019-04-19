#pragma once

#include <glad/glad.h>

class Texture
{
//this will be the texture class
//will be for importing any type of picture
//from texture normal map or else
private:

	size_t id;

	int width;
	int height;
	int nbChannel;

	bool flip;

public:

	//empty texture when none is loaded
	inline Texture() {};

	Texture(const char * texturePath, bool flipImage);

	//getter
	inline size_t getID() { return id; }
	inline int getWidth() { return width; }
	inline int getHeight() { return height; }
	inline int getNbChannel() { return nbChannel; }
	inline bool isFlip() { return flip; }

};

