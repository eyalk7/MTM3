# cmake_minimum_required(VERSION <specify CMake version here>)
project(MTM_EX3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -pedantic-errors -Werror -DNDEBUG")

add_executable(MTM_EX3 test2.cpp eurovision.cpp)