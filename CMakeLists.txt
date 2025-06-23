cmake_minimum_required(VERSION 3.10.0)
project(snake2d VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCES main.cpp game/Game.cpp game/Fruit.cpp game/Snake.cpp game/Vec2.cpp)
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    list(APPEND SOURCES render/Win32Window.cpp)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    list(APPEND SOURCES render/XWindow.cpp render/XDisplay.cpp)
    add_definitions(-DPLATFORM_LINUX)
endif()

add_executable(snake2d ${SOURCES})

# Linking Graphics library
if(WIN32)
    target_link_libraries(snake2d PRIVATE user32 gdi32)
elseif(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)

    target_include_directories(snake2d PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(snake2d PRIVATE ${X11_LIBRARIES})
endif()
