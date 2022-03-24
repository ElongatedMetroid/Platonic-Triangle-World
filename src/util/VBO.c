#include "../../include/VBO.h"

void VBO_Create(GLuint *VBO_ID, GLfloat *vertices, GLsizeiptr size){
	//generate buffers, make VBOID a reference the the buffers
    glGenBuffers(1, VBO_ID);
	//from now on any buffer calls we make on GL_ARRAY_BUFFER will be used to configure the currently bound buffer
    glBindBuffer(GL_ARRAY_BUFFER, *VBO_ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    //arg1: buffer we want to copy data into, arg2: size of the data in bytes, arg3: the user defined data, arg4: how we want the GPU to manage the data (options shown below)
    /*
        GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
        GL_STATIC_DRAW: the data is set only once and used many times.
        GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */
}

void VBO_Bind(GLuint VBO_ID){
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
}

void VBO_Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO_Delete(GLuint *VBO_ID){
    glDeleteBuffers(1, VBO_ID);
}
