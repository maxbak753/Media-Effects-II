cmake_minimum_required(VERSION 3.30)
project(particles_1)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV package
find_package(OpenCV REQUIRED)

#Include directories from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Specify the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

# # Specify the paths for FFTW3 and SndFile
# set(FFTW3_DIR "C:/vcpkg/installed/x64-windows/share/fftw3")
# set(SndFile_DIR "C:/vcpkg/installed/x64-windows/share/SndFile")

# # Find FFTW3 and Libsndfile
# find_package(FFTW3 REQUIRED)
# find_package(SndFile REQUIRED)

# Add the correct source file
add_executable(particles_1 particles_1.cpp)

# Link libraries
# target_link_libraries(particles_1 PRIVATE FFTW3::fftw3 sndfile)

#Link OpenCV libraries
target_link_libraries(particles_1 ${OpenCV_LIBS})