cmake_minimum_required(VERSION 3.10)

project(mc VERSION 1.0.0)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debugging
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(SndFile REQUIRED)

add_executable(mc src/main.cpp src/effects/autotune.cpp)

add_subdirectory(SoundTouch)
add_subdirectory(AudioFile)
add_subdirectory(FFT)



target_include_directories(mc PRIVATE SoundTouch/include)
target_include_directories(mc PRIVATE AudioFile)
target_include_directories(mc PRIVATE src/.)
target_include_directories(mc PRIVATE FFT)


# Link the SoundTouch library to your project
target_link_libraries(mc PRIVATE SoundTouch)
target_link_libraries(mc PRIVATE AudioFile)
target_link_libraries(mc PRIVATE kissfft)
target_link_libraries(mc PRIVATE SndFile::sndfile)
