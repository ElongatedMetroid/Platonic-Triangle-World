#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#define X 0
#define Y 1
#define Z 2
#define W 3

#define WIN_WIDTH 1080
#define WIN_HEIGHT 720
#define WIN_TITTLE "Platonic Triangle World"

#define VSHADER_PATH "../shaders/shader.vs"
#define FSHADER_PATH "../shaders/shader.fs"

#ifdef DEBON
    /*
        if DEBON is defined you can use the 
        DEBUG macro to display debug info 
        from the console
        fmt = what you want to display 
    */
    #define DEBUG(fmt, ...) printf(fmt, __VA_ARGS__)
#else
    /*
        does nothing if DEBON is not defined
    */
    #define DEBUG(fmt, ...) do { } while(0)
#endif  //DEBON


/*
    print an error message to the console and
    the current line and file then exit.
    fmt = what you want to display to the console
*/
#define ERROR(fmt) do{\
    fprintf(stderr, fmt);\
    printf("\nFILE: %s, LINE %d\n", __FILE__, __LINE__);\
    exit(EXIT_FAILURE);\
} while(0)

void *xcalloc(size_t multiplier, size_t size);
void *xmalloc(size_t size);

extern float deltaTime;     //time between current frame and last frame
extern float lastFrame;     //time between last frame

CGLM_INLINE
void
glm_vec3_mulsubs(vec3 a, float s, vec3 dest) {
  dest[0] -= a[0] * s;
  dest[1] -= a[1] * s;
  dest[2] -= a[2] * s;
}

#endif