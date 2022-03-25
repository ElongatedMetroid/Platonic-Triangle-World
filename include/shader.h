#ifndef SHADER_H_
#define SHADER_H_
#include <glad/glad.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

//the constuctor reads and builds the shader
int Shader_ReadAndBuild(GLuint *ShaderID, const char *vertexPath, const char *fragmentPath);
//use/activate the shader
void Shader_Use(GLuint ShaderID);
//utility uniform functions
void Shader_SetBool(GLuint ShaderID, const char *name, bool value);
void Shader_SetInt(GLuint ShaderID, const char *name, int value);
void Shader_SetFloat(GLuint ShaderID, const char *name, float value);
void Shader_SetMat4(GLuint ShaderID, const char *name, vec4 value);

#endif
