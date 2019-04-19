#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char * texturePath, bool flipImage)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	this->flip = flipImage;
	stbi_set_flip_vertically_on_load(flipImage);
	printf(texturePath);
	unsigned char * data = stbi_load(texturePath, &width, &height, &nbChannel, 0);
	if (data)
	{
		//printf("nb channel : %d", nbChannels);

		switch (nbChannel)
		{
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		default:
			break;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Texture from %s : Data not loaded", texturePath);
		exit(2);
	}
}
