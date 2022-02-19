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
  glfwSetCursorPosCallback(*window, camera_mouse_callback);

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

  //read the shaders from the vertex and fragment shader files, link them, and compile them (the program is referenced by ShaderID)
  Shader_ReadAndBuild(VSHADER_PATH, FSHADER_PATH);

  // create Vertex Array Object
  VAO_Create();
  // bind the created Vertex Array Object
  VAO_Bind();
  // create a Vertex Buffer Object
  VBO_Create(cubeVertices, cubeVerticesSize);
  // link layout 0, 3 elements, those elements are floats, the total size of each line in 5 floats, 0 floats to get to these elements 
  VAO_LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
  // link layout 1, 2 elements, those elements are floats, the total size of each line is 5 floats, 3 floats to get to these elements
  VAO_LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

  // unbind Vertex objects/references from buffers
  VBO_Unbind();
  VAO_Unbind();
	
  //create 2 texture references, one for awesome face and the other for grass
  GLuint texture_awesomeface, texture_grass;
  //Texture reference, texture path, type of texture, texture slot, format, and pixel type 
  Texture_Load(&texture_awesomeface, "../textures/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  Texture_Load(&texture_grass, "../textures/grass.jpeg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

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
    processCameraInput(window);

    // Color to clear the screen with
    glClearColor(0.00f, 0.10f, 0.20f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the active textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_awesomeface);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_grass);

	// Make sure we are using the shaders we specified earlier	
    Shader_Use();
    // update camera positions
    Camera_Update();

	// bind Vertex Array Object/reference because following this we will be drawing to the buffer 
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

  // destroy the glfw window
  glfwDestroyWindow(window);
  // clean up
  glfwTerminate();

  return 0;
}
