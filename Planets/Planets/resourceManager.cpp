#include "resourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, std::string name)
{
	return shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
}

Shader ResourceManager::GetShader(std::string name)
{
	return shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	return textures[name] = LoadTextureFromFile(file, alpha);
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return textures[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : shaders)
		glDeleteProgram(iter.second.id);
	// (Properly) delete all textures
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.id);
}

Shader ResourceManager::LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.internal_format = GL_RGBA;
		texture.image_format = GL_RGBA;
	}

	int width, height;
	
	unsigned char* image = stbi_load(file, &width, &height, nullptr, texture.image_format == GL_RGBA ? 4 : 3);

	texture.Generate(width, height, image);

	stbi_image_free(image);
	return texture;
}