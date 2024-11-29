cmake_minimum_required(VERSION 3.10)

project(AutoTune VERSION 1.0.0)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debugging
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(SndFile REQUIRED)

add_executable(AutoTune src/main.cpp src/autotune.cpp)

add_subdirectory(SoundTouch)
add_subdirectory(AudioFile)
add_subdirectory(FFT)



target_include_directories(AutoTune PRIVATE SoundTouch/include)
target_include_directories(AutoTune PRIVATE AudioFile)
target_include_directories(AutoTune PRIVATE src)
target_include_directories(AutoTune PRIVATE FFT)


# Link the SoundTouch library to your project
target_link_libraries(AutoTune PRIVATE SoundTouch)
target_link_libraries(AutoTune PRIVATE AudioFile)
target_link_libraries(AutoTune PRIVATE kissfft)
target_link_libraries(AutoTune PRIVATE SndFile::sndfile)
