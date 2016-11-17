cmake_minimum_required(VERSION 3.5)

project(Mason)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include_directories(Engine/include)

add_subdirectory(Engine)
add_subdirectory(Game)