cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

set(CMAKE_CXX_STANDARD 17)

project(graphicspipe)

find_library(SDL2 /usr/include/)
add_library(state STATIC state.cpp)
add_library(physicspipeline STATIC physicspipeline.cpp)
target_link_libraries(physicspipeline state)
add_library(graphicspipeline STATIC graphicspipeline.cpp)
target_link_libraries(graphicspipeline SDL2 physicspipeline)

add_executable(graphicspipe main.cpp)
target_link_libraries(graphicspipe state physicspipeline graphicspipeline)

install(TARGETS graphicspipe DESTINATION bin)
