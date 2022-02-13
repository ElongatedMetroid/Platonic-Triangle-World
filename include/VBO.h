#ifndef VBO_H_
#define VBO_H_

#include <glad/glad.h>

//VBO: Vertex Buffer Object
extern GLuint VBOID;

void VBO_Create(GLfloat *vertices, GLsizeiptr size);
void VBO_Bind();
void VBO_Unbind();
void VBO_Delete();

#endif
