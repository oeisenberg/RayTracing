cmake_minimum_required(VERSION 3.10)

# set the project name
project(CM30075)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(finalexecutable raytracer.cpp framebuffer.cpp linedrawer.cpp camera.cpp sphere.cpp scene.cpp plane.cpp triangle.cpp polymesh.cpp material.cpp spotlight.cpp pointlight.cpp ap.cpp alglibmisc.cpp alglibinternal.cpp)