cmake_minimum_required(VERSION 3.10)
project(OpenGLExample)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp glad/src/glad.c)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)

include_directories(glad/include)

# Add your source files
add_executable(OpenGLExample ${SOURCE_FILES})

# Link libraries
target_link_libraries(OpenGLExample ${OPENGL_LIBRARIES} glfw "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")