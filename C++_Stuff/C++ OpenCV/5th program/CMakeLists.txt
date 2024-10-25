cmake_minimum_required(VERSION 3.5.0)
project(opencv_test VERSION 0.1.0 LANGUAGES C CXX)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV package
find_package(OpenCV REQUIRED)

#Include directories from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Create an executable
add_executable(OpenCVExample main.cpp)

#Link OpenCV libraries
target_link_libraries(OpenCVExample ${OpenCV_LIBS})


# cmake_minimum_required(VERSION 3.5.0)
# project(opencv_test VERSION 0.1.0 LANGUAGES C CXX)

# #
# set(CMAKE_CXX_STANDARD 17)

# # Create an executable
# add_executable(opencv_test main.cpp)

# # -------------------------------------
# # Open CV - - - - - - - - - - - - - - -
# # Find OpenCV package
# find_package(OpenCV REQUIRED)
# #Include directories from OpenCV
# include_directories(${OpenCV_INCLUDE_DIRS})
# #Link OpenCV libraries
# target_link_libraries(opencv_test ${OpenCV_LIBS})