cmake_minimum_required(VERSION 3.5)
project(Mason)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -wd4251")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")


#########################################################
# FIND OPENGL
#########################################################
IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
ELSE (APPLE)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    IF(UNIX)
        find_package(GLEW REQUIRED)
    ELSE(UNIX)
        find_package(glew REQUIRED)
    ENDIF(UNIX)
    include_directories(${GLEW_INCLUDE_DIR})
    SET(EXTRA_LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
ENDIF (APPLE)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Box2D
find_package(Box2D REQUIRED)
include_directories(${BOX2D_INCLUDE_DIR})

# GLM -- on Windows: depends on env var: GLM_ROOT_DIR
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})


find_package(SRE REQUIRED)
if (SRE_FOUND)
    include_directories(${SRE_INCLUDE_DIR})
ELSE (SRE_FOUND)
    MESSAGE( STATUS "Failed to find Simple Render Engine")
endif(SRE_FOUND)

find_package(SDL_MIXER REQUIRED)
if (SDLMIXER_FOUND)
    include_directories(${SDL_MIXER_INCLUDE_DIRS})
ELSE (SDLMIXER_FOUND)
    MESSAGE( STATUS "Failed to find SDL Mixer")
endif(SDLMIXER_FOUND)


add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(Demo)
add_subdirectory(Demo_Particles)
add_subdirectory(Demo_Piano)