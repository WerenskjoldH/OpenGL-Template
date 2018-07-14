#pragma once
#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader>	shaders;
	static std::map<std::string, Texture2D> textures;

	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	
	static Shader GetShader(std::string name);

	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);

	static Texture2D GetTexture(std::string name);

	static void Clear();

private:
	// Since functions and variables are static, we do not want any ResourceManager objects to exist
	ResourceManager() {}

	static Shader LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShader = nullptr);

	static Texture2D LoadTextureFromFile(const GLchar *file, GLboolean alpha);
};