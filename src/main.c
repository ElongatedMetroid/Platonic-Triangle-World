#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

#include "../include/VAO.h"
#include "../include/VBO.h"
#include "../include/camera.h"
#include "../include/common.h"
#include "../include/cube.h"
#include "../include/input.h"
#include "../include/shader.h"
#include "../include/texture.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { // gets called everytime the window is resized
  glViewport(0, 0, width, height);
}

void initGame(GLFWwindow **window) {
  // initialize GLFW
  if (glfwInit() == GLFW_FALSE)
    ERROR("Could not initialize GLFW!\n");

  // Tell GLFW what version of openGL we are using, here we are using openGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Tell GLFW we are using the core profile of openGL this means we only have
  // the newer functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFW window that is 1080x 720x and has a tittle Platonic Triangle
  // World
  *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITTLE, NULL, NULL);

  // check if the window created was a success
  if (!*window)
    ERROR("Could not create GLFW window!\n");

  // Tell GLFW we want to use the window
  glfwMakeContextCurrent(*window);
  glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
  glfwSetCursorPosCallback(*window, mouse_callback);

  glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // load glad witch will find all the functions OpenGL needs to operate
  // the function glfwGetProcAddress defines the correct funtion based on the OS
  // were compiling for
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    ERROR("Failed to initialize glad!\n");

  // enable depth testing, this allows models to be drawn in the correct order
  // (no overlapping)
  glEnable(GL_DEPTH_TEST);

  // area of the window we want openGL to render in
  // x = 0, y = 0, to x = 1080, y = 720
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
}

int main(void) {
  GLFWwindow *window = NULL;

  initGame(&window);

  Shader_ReadAndBuild(VSHADER_PATH, FSHADER_PATH);

  // create Vertex Array Object
  VAO_Create();
  // bind the created Vertex Array Object
  VAO_Bind();
  // create a Vertex Buffer Object
  VBO_Create(cubeVertices, cubeVerticesSize);
  VAO_Link();

  initTextures();

  // use the created shader program
  Shader_Use();
  // set texture1 to 0
  Shader_SetInt("texture1", 0);
  // set texture2 to 1
  Shader_SetInt("texture2", 1);

  // updates every frame
  while (!glfwWindowShouldClose(window)) {
    // get delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // process any input
    processInput(window);

    // Color to clear the screen with
    glClearColor(0.00f, 0.10f, 0.20f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the active textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    Shader_Use();
    // update camera positions
    Camera_Update();

    VAO_Bind();

    for (unsigned int rows = 0; rows < 100; rows++) {
      for (unsigned int col = 0; col < 100; col++) {
        vec3 cubePos = {col, 0, rows};
        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model, cubePos);
        Shader_SetMat4("model", (float *)model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
      }
    }

    // swap back buffer with front buffer
    glfwSwapBuffers(window);

    // process all events that may occur
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
