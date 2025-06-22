cmake_minimum_required(VERSION 3.10.0)
project(snake2d VERSION 0.1.0 LANGUAGES C CXX)

set(sources main.cpp game/Game.cpp game/Fruit.cpp game/Snake.cpp game/Vec2.cpp)

if(WIN32)

elseif(UNIX AND NOT APPLE)
    list(APPEND SOURCES render/XWindow.cpp render/XDisplay.cpp)
    add_definitions(-DPLATFORM_LINUX)
endif()

add_executable(snake2d main.cpp game/Game.cpp game/Fruit.cpp game/Snake.cpp render/XDisplay.cpp render/XWindow.cpp game/Vec2.cpp)

# Linking X11
find_package(X11 REQUIRED)

target_include_directories(snake2d PRIVATE ${X11_INCLUDE_DIR})
target_link_libraries(snake2d PRIVATE ${X11_LIBRARIES})