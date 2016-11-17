set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")


file(GLOB SOURCE_FILES
  "src/*.c"
  "src/*.cpp"
  "include/*.h"
  "include/*.hpp"
)

include_directories(include)

add_library(Mason ${SOURCE_FILES})
target_link_libraries(Mason ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SRE_LIBRARY} ${BOX2D_LIBRARY})

