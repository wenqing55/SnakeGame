cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    main.cpp
    Game.cpp
    Snake.cpp
    Food.cpp
    Renderer.cpp
    Input.cpp
    SaveSystem.cpp
)

add_executable(SnakeGame ${SOURCES})

if(WIN32)
    target_link_libraries(SnakeGame PRIVATE user32)
endif()