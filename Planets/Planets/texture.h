#pragma once
#include <glad/glad.h>

class Texture2D
{
public:
	/// Variable ///
	GLuint id;
	
	GLuint width, height;
	
	GLuint internal_format;
	GLuint image_format;

	GLuint wrap_s;
	GLuint wrap_t;
	GLuint filter_min;
	GLuint filter_max;

	/// Constructors & Deconstructors ///
	Texture2D();

	/// Functions & Methods ///
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind() const;

};