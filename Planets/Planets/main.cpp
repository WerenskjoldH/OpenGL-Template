#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resourceManager.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
GLFWwindow *window;

void Error_Callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int Initialize()
{

	glfwSetErrorCallback(Error_Callback);

	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Planets - Hunter Werenskjold", NULL, NULL);

	if (!window)
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	game.Init();

	return 1;
}

void Cleanup()
{
	ResourceManager::Clear();
	glfwTerminate();
}

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			game.keys[key] = 1;
		else if (action == GLFW_RELEASE)
			game.keys[key] = 0;
	}
}

int main()
{

	if (!Initialize())
		return -1;

	GLfloat deltaTime = 0.f;
	GLfloat lastFrame = 0.f;

	game.state = GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame= glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		game.ProcessInput(deltaTime);

		game.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		game.Render();

		glfwSwapBuffers(window);
	}

	Cleanup();

    return 0;
}

