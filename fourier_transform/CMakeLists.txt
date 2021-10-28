cmake_minimum_required(VERSION 3.20)
project(fourier_transform)

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

add_executable(
    fourier
    src/main.cpp
    include/matrix.hpp
    include/fs.hpp
    src/fs.cpp
    include/fft.hpp src/fft.cpp include/util.hpp include/sft.hpp src/sft.cpp src/util.cpp include/img_transform.hpp src/img_transform.cpp)
