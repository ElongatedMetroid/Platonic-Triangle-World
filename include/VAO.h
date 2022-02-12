#ifndef VAO_H_
#define VAO_H_

#include <stdlib.h>
#include <glad/glad.h>
#include "VBO.h"

extern GLuint VAOID;

void VAO_Create();
void VAO_Link();
void VAO_Bind();
void VAO_Unbind();
void VAO_Delete();

#endif