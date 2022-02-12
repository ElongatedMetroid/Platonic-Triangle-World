#include "../../include/input.h"

void processInput(GLFWwindow *window){
    //buffers to temp store answers
    vec3 v;
    vec3 vv;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glm_vec3_muladds(cameraFront, cameraSpeed, cameraPos);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glm_vec3_mulsubs(cameraFront, cameraSpeed, cameraPos);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        glm_vec3_cross(cameraFront, cameraUp, v);
        glm_normalize_to(v, vv);
        glm_vec3_mulsubs(vv, cameraSpeed, cameraPos);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        glm_vec3_cross(cameraFront, cameraUp, v);
        glm_normalize_to(v, vv);
        glm_vec3_muladds(vv, cameraSpeed, cameraPos);
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow *window, double xpos, double ypos){
    float lastX = (float)WIN_WIDTH/ 2.0;
    float lastY = (float)WIN_HEIGHT/ 2.0;
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;   //reversed: Y ranges bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    vec3 front;
    front[X] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    front[Y] = sin(glm_rad(pitch));
    front[Z] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
    glm_normalize_to(front, cameraFront);

    glfwSetCursorPos(window, (double)WIN_WIDTH/2, (double)WIN_HEIGHT/2);
}
