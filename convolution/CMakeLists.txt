cmake_minimum_required(VERSION 3.20)
project(convolution)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(./include /usr/include)
link_directories(/usr/lib)

link_libraries(
    -lsfml-audio
    -lsfml-graphics
    -lsfml-network
    -lsfml-system
    -lsfml-window
    pthread
)

add_executable(convolution src/main.cpp include/file_not_found.hpp src/file_not_found.cpp include/mask.hpp src/mask.cpp)
