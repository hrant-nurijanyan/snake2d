cmake_minimum_required(VERSION 3.24)
project(snake2d)

set(CMAKE_CXX_STANDARD 17)

add_executable(snake2d main.cpp)

set(EXT_DEPS_DIR extDeps)

# GLFW
set(GLFW_DIR ${EXT_DEPS_DIR}/glfw)
set(GLFW_INC_DIR ${GLFW_DIR}/include)

# GLAD
set(GLAD_DIR ${EXT_DEPS_DIR}/glad)
set(GLAD_INC_DIR ${GLAD_DIR}/include)

# Linking all together
add_subdirectory(${GLAD_DIR})
add_subdirectory(${GLFW_DIR})

find_package(OpenGL REQUIRED)

target_link_libraries(snake2d PRIVATE glfw OpenGL::GL glad)
target_include_directories(snake2d PRIVATE ${GLFW_INC_DIR} ${GLAD_INC_DIR})