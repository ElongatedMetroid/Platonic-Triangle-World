#include "../../include/VAO.h"

void VAO_Create(GLuint *VAO_ID){
	//make a reference to VAO the VAO NEEDS to be genereated before the VBO
    glGenVertexArrays(1, VAO_ID);
}

void VAO_LinkAttrib(GLuint VAO_ID, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset){
    VBO_Bind(VAO_ID);
    //To get the next attribute value (e.g. the next x component of the position vector) in the data array we have to move 5 floats to the right; 5 * sizeof(float)
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	//to use it we need to enable it we pass in 0 because that is the location of our vertex attribute
    glEnableVertexAttribArray(layout);
    VBO_Unbind();
}

void VAO_Bind(GLuint VAO_ID){
    glBindVertexArray(VAO_ID);
}

void VAO_Unbind(){
    glBindVertexArray(0);
}

void VAO_Delete(GLuint *VAO_ID){
    glDeleteVertexArrays(1, VAO_ID);
}
