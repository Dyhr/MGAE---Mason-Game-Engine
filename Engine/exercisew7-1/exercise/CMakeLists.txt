cmake_minimum_required(VERSION 3.6)
project(GameplaySystems)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB SOURCE_FILES
        "src/*.hpp"
        "src/*.h"
        "src/*.cpp"
        )

add_executable(GameplaySystemsProgram ${SOURCE_FILES})