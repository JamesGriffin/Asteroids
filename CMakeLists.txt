
cmake_minimum_required(VERSION 3.5)
project(asteroids)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(src)

set(SOURCE_FILES
    src/main.cpp
    src/display.cpp
    src/space_object.cpp
    src/ship.cpp
    src/bullet.cpp
    src/asteroid.cpp
    src/asteroids_game.cpp
)

add_executable(asteroids ${SOURCE_FILES})

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

target_link_libraries(asteroids
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARIES}
    SDL2_mixer
)

add_custom_target(run
    COMMAND asteroids
    DEPENDS asteroids
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
