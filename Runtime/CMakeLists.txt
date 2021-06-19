
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES
    "src/*.h"
    "src/*.hpp"
    "src/*.c"
    "src/*.cpp"
    "src/*.m"
    "src/*.mm"
)

add_executable(Runtime src/Emerald/main.cpp)
target_sources(Runtime PUBLIC ${SRC_FILES})
target_include_directories(Runtime PUBLIC "src")

