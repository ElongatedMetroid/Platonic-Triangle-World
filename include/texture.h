#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "external/stb_image.h"
#include "common.h"

extern int texture1, texture2;

void initTextures(void);

#endif