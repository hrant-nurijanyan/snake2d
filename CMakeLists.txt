cmake_minimum_required(VERSION 3.24)
project(snake2d)

set(CMAKE_CXX_STANDARD 17)

add_executable(snake2d main.cpp)

set(EXT_DEPS_DIR extDeps)

# GLAD
set(GLAD_DIR ${EXT_DEPS_DIR}/glad)
set(GLAD_INC_DIR ${GLAD_DIR}/include)

# Linking all together
add_subdirectory(${GLAD_DIR})

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)


target_link_libraries(snake2d PRIVATE glfw OpenGL::GL glad)
target_include_directories(snake2d PRIVATE ${GLAD_INC_DIR})