#ifndef INPUT_H_
#define INPUT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "camera.h"
#include "common.h"

void processCameraInput(GLFWwindow *window);
void camera_mouse_callback(GLFWwindow *window, double xpos, double ypos);

#endif //INPUT_H_
