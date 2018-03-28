cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -Ofast")

set(CMAKE_CXX_STANDARD 17)

project(game)

find_library(SDL2 REQUIRED)
find_library(SDL2_image REQUIRED)
add_library(state STATIC state.cpp)
add_library(texture STATIC texture.cpp)
target_link_libraries(state SDL2)
target_link_libraries(texture SDL2 SDL2_image)
add_library(physicspipeline STATIC physicspipeline.cpp)
add_library(graphicspipeline STATIC graphicspipeline.cpp)
target_link_libraries(graphicspipeline texture physicspipeline)
add_library(physicshelper STATIC physicshelper.cpp)

add_executable(game main.cpp)
target_link_libraries(game state graphicspipeline physicshelper)

install(TARGETS game DESTINATION bin)
