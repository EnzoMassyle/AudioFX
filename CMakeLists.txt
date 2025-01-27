cmake_minimum_required(VERSION 3.12)
project(mc VERSION 1.0.0)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debugging
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")


find_package(SndFile REQUIRED)
find_package(FFTW3 CONFIG REQUIRED)

add_executable(mc src/main.cpp src/effects/autotune.cpp src/effects/fft.cpp)

target_include_directories(mc PRIVATE src/effects/.)
target_link_libraries(mc PRIVATE SndFile::sndfile)
target_link_libraries(mc PRIVATE FFTW3::fftw3)