file(GLOB GAME_SOURCE_FILES
	"src/*.c"
	"src/*.cpp"
	"src/*.h"
	"src/*.hpp"
)

include_directories(../Engine/include)

add_executable(Game ${GAME_SOURCE_FILES})
target_link_libraries(Game ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} Mason)
