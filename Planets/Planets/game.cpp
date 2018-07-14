#include "game.h"
#include "resourceManager.h"
#include "spriteRenderer.h"

#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer *renderer;

Game::Game(GLuint width, GLuint height)
	: state(GAME_ACTIVE), keys(), width(width), height(height)
{

}

Game::~Game()
{
	delete renderer;
}

void Game::Init()
{
	ResourceManager::LoadShader("Shaders/default.vert", "Shaders/default.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	ResourceManager::LoadTexture("Textures/Default_Planet.png", GL_TRUE, "test");

	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

}

void Game::Update(GLfloat dt)
{

}

void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
	renderer->DrawSprite(ResourceManager::GetTexture("test"), glm::vec2(200, 200), glm::vec2(300, 300), 0.f, glm::vec3(1.0f, 1.0f, 1.0f));
}
