cmake_minimum_required(VERSION 3.5.0)
project(fun1 VERSION 0.1.0 LANGUAGES C CXX)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV package
find_package(OpenCV REQUIRED)

#Include directories from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Create an executable
add_executable(fun1 fun1.cpp)

#Link OpenCV libraries
target_link_libraries(fun1 ${OpenCV_LIBS})