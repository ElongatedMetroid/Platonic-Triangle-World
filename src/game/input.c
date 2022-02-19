#include "../../include/input.h"

void processCameraInput(GLFWwindow *window){
    //vector buffers to temp store answers
    vec3 v;
    vec3 vv;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)       //if escape is pressed, exit
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)            //if w is pressed add camera speed to camera front (move camera forward)
        glm_vec3_muladds(cameraFront, cameraSpeed, cameraPos);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)            //if s is press substract camera speed from camera front (move camera backwards)
        glm_vec3_mulsubs(cameraFront, cameraSpeed, cameraPos);  
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){           //if a is pressed get the cross product of cameraFront and cameraUp
        glm_vec3_cross(cameraFront, cameraUp, v);               //store it in v
        glm_normalize_to(v, vv);                                //normalize v store solution in vv
        glm_vec3_mulsubs(vv, cameraSpeed, cameraPos);           //subtract vv from camera speed store in camera pos (move left)
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){           
        glm_vec3_cross(cameraFront, cameraUp, v);
        glm_normalize_to(v, vv);
        glm_vec3_muladds(vv, cameraSpeed, cameraPos);
    }
}

bool firstMouse = true;
void camera_mouse_callback(GLFWwindow *window, double xpos, double ypos){
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

	//move cursor to center or the screen
    glfwSetCursorPos(window, (double)WIN_WIDTH/2, (double)WIN_HEIGHT/2);
}
