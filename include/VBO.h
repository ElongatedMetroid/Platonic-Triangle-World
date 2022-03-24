#ifndef VBO_H_
#define VBO_H_

#include <glad/glad.h>

void VBO_Create(GLuint *VBO_ID, GLfloat *vertices, GLsizeiptr size);
void VBO_Bind(GLuint VBO_ID);
void VBO_Unbind();
void VBO_Delete(GLuint *VBO_ID);

#endif
