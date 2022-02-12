#ifndef CAMERA_H_
#define CAMERA_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/types.h>
#include "common.h"
#include "shader.h"

extern float cameraSpeed;

extern vec3 cameraFront;
extern vec3 cameraPos;
extern vec3 cameraUp;

extern float yaw;
extern float pitch;

extern mat4 view;
extern mat4 projection;

extern void Camera_Update();

#endif //CAMERA_H_