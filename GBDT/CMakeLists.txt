cmake_minimum_required(VERSION 3.13)
project(GBDT)

set(CMAKE_CXX_STANDARD 11)

add_executable(GBDT main.cpp dataset.cpp gbdt.cpp cart.cpp dataset.h cart.h gbdt.h)