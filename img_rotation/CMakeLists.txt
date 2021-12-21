cmake_minimum_required(VERSION 3.20)
project(img_rotation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(./include /usr/include)
link_directories(/usr/lib)

link_libraries(
    -lsfml-graphics
    -lsfml-system
    -lsfml-window
    pthread
)

add_executable(
    img_rotation
    src/main.cpp
    include/util.hpp
    src/util.cpp
    include/image_rotation.hpp
    src/image_rotation.cpp
    include/pixel_approximation.hpp
    src/pixel_approximation.cpp
    include/image_scaling.hpp
    src/image_scaling.cpp
    include/distortion_correction.hpp
    src/distortion_correction.cpp
)
