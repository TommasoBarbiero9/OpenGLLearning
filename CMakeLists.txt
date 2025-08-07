cmake_minimum_required(VERSION 3.10)
project(OpenGLExample)

set(CMAKE_CXX_STANDARD 11)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)

# Add your source files
add_executable(OpenGLExample main.cpp)

# Link libraries
target_link_libraries(OpenGLExample ${OPENGL_LIBRARIES} glfw)