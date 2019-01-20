# cmake_minimum_required(VERSION <specify CMake version here>)
project(BasicML)

set(CMAKE_CXX_STANDARD 11)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(BasicML main.cpp kmeans.cpp dataset.cpp)