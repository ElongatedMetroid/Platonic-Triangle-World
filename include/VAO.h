#ifndef VAO_H_
#define VAO_H_

#include <stdlib.h>
#include <glad/glad.h>
#include "VBO.h"

void VAO_Create(GLuint *VAO_ID);
void VAO_LinkAttrib(GLuint VAO_ID, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
void VAO_Bind(GLuint VAO_ID);
void VAO_Unbind();
void VAO_Delete(GLuint *VAO_ID);

#endif
