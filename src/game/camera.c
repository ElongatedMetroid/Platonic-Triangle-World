#include "../../include/camera.h"

vec3 cameraFront = {0.0f, 0.0f, -1.0f};
vec3 cameraPos = {0.0f, 4.0f, 3.0f};
vec3 cameraUp = {0.0f, 1.0f, 0.0f};

float yaw = -90.0f;
float pitch = 0.0f;

mat4 view;
mat4 projection;

float cameraSpeed = 0.0f;

void Camera_Update(GLuint ShaderID) {
  // set camera speed to 1.5f
  cameraSpeed = 10.5f * deltaTime;

  glm_perspective(glm_rad(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f,
                  100.0f, projection);
  Shader_SetMat4(ShaderID, "projection", (float *)projection);

  vec3 camPosAddCamFront;
  glm_vec3_add(cameraPos, cameraFront, camPosAddCamFront);
  glm_lookat(cameraPos, camPosAddCamFront, cameraUp, view);
  Shader_SetMat4(ShaderID, "view", (float *)view);
}
