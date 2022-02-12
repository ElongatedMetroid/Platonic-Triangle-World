#include "../../include/VAO.h"

GLuint VAOID = 0;

void VAO_Create(){
    glGenVertexArrays(1, &VAOID);
}

void VAO_Link(){
    VBO_Bind();
    //To get the next attribute value (e.g. the next x component of the position vector) in the data array we have to move 5 floats to the right; 5 * sizeof(float)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //VBO_Unbind();
}

void VAO_Bind(){
    glBindVertexArray(VAOID);
}

void VAO_Unbind(){
    glBindVertexArray(0);
}

void VAO_Delete(){
    glDeleteVertexArrays(1, &VAOID);
}