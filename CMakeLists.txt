cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

set(CMAKE_CXX_STANDARD 17)

project(game)

find_library(SDL2 /usr/include/)
add_library(state STATIC state.cpp)
target_link_libraries(state SDL2)
add_library(physicspipeline STATIC physicspipeline.cpp)
add_library(graphicspipeline STATIC graphicspipeline.cpp)
target_link_libraries(graphicspipeline SDL2 physicspipeline)

add_executable(game main.cpp)
target_link_libraries(game state graphicspipeline)

install(TARGETS game DESTINATION bin)
