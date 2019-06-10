#include <iostream>
#include <time.h>
#include "Input.h"
#include "window.h"
#include "Shader.h"
#include "Object.h"
#include "Camera.h"



int main()
{

	Creatio::Window window("test", 4, 5, 1000, 1000, false);
	Creatio::Input * input = Creatio::Input::init(window);
	Creatio::Shader tex("shader/vertex.glsl", "shader/texture.glsl");
	Creatio::Shader light("shader/vertex.glsl", "shader/white.glsl");

	float box[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	float flat[] = {
		// positions            // normals         // texcoords
		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};

	glActiveTexture(GL_TEXTURE0);
	Creatio::Texture cobble("texture/cobble.png", false);
	glActiveTexture(GL_TEXTURE1);
	Creatio::Texture sand("texture/sand.jpg", false);
	Creatio::Object cube(box, 36, cobble);
	Creatio::Object plane(flat, 6, sand);
	Creatio::Camera cam(window.getWidth(), window.getHeight());
	tex.use();
	tex.setMat4((char *)"projection", cam.getProj());

	light.use();
	light.setMat4((char *)"projection", cam.getProj());

	//render loop
	glViewport(0, 0, window.getWidth(), window.getHeight());
	while (!glfwWindowShouldClose(window.display))
	{
		input->pollEvent();
		cam.update();

		glm::vec3 lightPos = glm::vec3(glm::vec3(sin(window.getTime()) * 2, sin(window.getTime()) + 1.f, cos(window.getTime()) * 2));

		{
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		{
			tex.use();
			tex.setVec3((char *)"iResolution", (float)window.getWidth(), (float)window.getHeight(), 0.f);
			tex.setFloat((char *)"iTime", window.getTime());
			tex.setVec3((char *)"iColor", glm::vec3(1.0f, 1.0f, 1.0f));
			tex.setInt((char *)"tex",0);
			tex.setInt((char *)"normalTex", 1);
			tex.setVec3((char *)"lightPos", lightPos);
			cam.setView(glm::lookAt(cam.getPos(),cam.getPos() + cam.getFront(), cam.getUp()));
			tex.setMat4("view", cam.getView());
		}


		{
			tex.setInt((char *)"tex", 1);
			tex.setInt((char *)"normalTex", 0);
		}

		cube.start();
		cube.translate(glm::vec3(0.f, 1.f, 0.f));
		tex.setMat4("transform", cube.getTrans());
		cube.show();

		plane.start();
		tex.setMat4("transform", plane.getTrans());
		plane.show();

		light.use();
		light.setMat4("view", cam.getView());
		cube.start();
		cube.translate(lightPos);
		cube.scale(glm::vec3(0.2f));
		light.setMat4("transform", cube.getTrans());
		cube.show();

	}
	glfwTerminate();
	return 0;
}