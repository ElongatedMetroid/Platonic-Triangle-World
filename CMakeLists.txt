cmake_minimum_required(VERSION 3.0.0)
project(PlatonicTriangleWorld VERSION 0.1.0)

add_executable(PlatonicTriangleWorld glad.c include/external/stb_image.c src/model/cube.c src/game/camera.c src/game/input.c src/util/common.c src/util/shader.c src/util/texture.c src/util/VAO.c src/util/VBO.c src/main.c)

target_link_libraries(PlatonicTriangleWorld GL glfw3 pthread m dl Xi Xrandr X11)