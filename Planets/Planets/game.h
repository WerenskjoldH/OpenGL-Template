#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	/// Variables ///
	GameState	state;
	GLboolean	keys[1024];
	GLuint		width, height;

	/// Constructors & Destructors ///
	Game(GLuint width, GLuint height);
	~Game();

	/// Methods & Functions ///
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

private:

};