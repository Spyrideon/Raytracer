cmake_minimum_required(VERSION 3.16)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings
if(MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus)
else()
    add_compile_options(-g -Wall -Wextra -Wpedantic)
    # for larger stack on non-msvc linker:
    # add_link_options(-Wl,--stack,16777216)
endif()

# ---- Main executable ----
add_executable(raytracer
        src/raytracer.cc
        src/math.cc
        src/geometry.cc
        src/Screen.cpp
        src/Camera.cpp
        include/Color.h
        include/Material.h
        include/Material.h
        include/Object.h
        include/Object.h
        include/SphereObject.h
        include/SphereObject.h
        include/TriangleObject.h
)

target_include_directories(raytracer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

