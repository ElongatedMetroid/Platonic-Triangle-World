#ifndef SHADER_H_
    #define SHADER_H_
#include <glad/glad.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

// the program ID
extern unsigned int ShaderID;
//the constuctor reads and builds the shader
int Shader_ReadAndBuild(const char *vertexPath, const char *fragmentPath);
//use/activate the shader
void Shader_Use();
//utility uniform functions
void Shader_SetBool(const char *name, bool value);
void Shader_SetInt(const char *name, int value);
void Shader_SetFloat(const char *name, float value);
void Shader_SetMat4(const char *name, vec4 value);

#endif