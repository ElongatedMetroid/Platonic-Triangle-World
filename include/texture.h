#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "external/stb_image.h"
#include "common.h"
#include "shader.h"

void Texture_Load(GLuint *ID, const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

void Texture_TexUnit(const char *uniform, GLuint unit);

void Texture_Bind(GLenum type, GLuint *ID);
void Texture_Unbind(GLenum type, GLuint *ID);
void Texture_Delete(GLenum type, GLuint *ID);

#endif
