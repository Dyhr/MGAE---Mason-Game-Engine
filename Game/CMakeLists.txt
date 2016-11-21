file(GLOB_RECURSE GAME_SOURCE_FILES
	"src/*.c"
	"src/*.cpp"
	"src/*.h"
	"src/*.hpp"
	"data/*.json"
)

include_directories(../Engine/include)

add_executable(Game ${GAME_SOURCE_FILES})
target_link_libraries(Game ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SRE_LIBRARY} ${BOX2D_LIBRARY} Mason)


IF (WIN32)
    SET(SDL2_dll "" CACHE FILEPATH "Where the SDL2.dll can be found")
    SET(SDL2_image_dll "" CACHE FILEPATH "Where the SDL2_image.dll can be found")
    SET(libjpeg-9_dll "" CACHE FILEPATH "Where the libjpeg-9.dll can be found")
    SET(libpng16-16_dll "" CACHE FILEPATH "Where the libpng16-16.dll can be found")
    SET(libtiff-5_dll "" CACHE FILEPATH "Where the libtiff-5.dll can be found")
    SET(libwebp-4_dll "" CACHE FILEPATH "Where the libwebp-4.dll can be found")
    SET(zlib1_dll "" CACHE FILEPATH "Where the zlib1.dll can be found")
    SET(DLLFileList ${libjpeg-9_dll} ${libpng16-16_dll} ${SDL2_dll} ${SDL2_image_dll} ${zlib1_dll} ${libtiff-5_dll} ${libwebp-4_dll})
ENDIF(WIN32)

file(COPY ${DLLFileList} DESTINATION Debug)
file(COPY ${DLLFileList} DESTINATION Release)