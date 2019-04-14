cmake_minimum_required(VERSION 3.13)
project(dynamic_solver)

set(CMAKE_CXX_STANDARD 17)

add_executable(dynamic_solver main.cpp solver.h)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(dynamic_solver ${PYTHON_LIBRARIES})

