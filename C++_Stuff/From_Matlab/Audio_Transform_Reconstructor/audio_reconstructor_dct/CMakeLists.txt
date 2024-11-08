cmake_minimum_required(VERSION 3.30)

project(ar_dct)

set(CMAKE_CXX_STANDARD 17)

# Specify the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

# Specify the paths for FFTW3 and SndFile
set(FFTW3_DIR "C:/vcpkg/installed/x64-windows/share/fftw3")
set(SndFile_DIR "C:/vcpkg/installed/x64-windows/share/SndFile")

# Find FFTW3 and Libsndfile
find_package(FFTW3 REQUIRED)
find_package(SndFile REQUIRED)

# Add the correct source file
add_executable(ar_dct ar_dct.cpp)

# Link libraries (use fftw3 instead of fftw3f)
target_link_libraries(ar_dct PRIVATE FFTW3::fftw3 sndfile)
