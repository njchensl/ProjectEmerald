
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES
    "src/*.h"
    "src/*.hpp"
    "src/*.c"
    "src/*.cpp"
    "src/*.m"
    "src/*.mm"
)

find_package(boost CONFIG REQUIRED COMPONENTS thread)

add_executable(Runtime src/Emerald/main.cpp)

include_directories(${Boost_INCLUDE_DIRS})
link_libraries(Runtime ${Boost_LIBRARIES})

target_sources(Runtime PUBLIC ${SRC_FILES})
target_include_directories(Runtime PUBLIC "src")
#target_link_libraries(Runtime PUBLIC boost)

