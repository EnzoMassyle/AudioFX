# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Name of your project
project(AutoTune VERSION 1.0.0)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debugging
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Add your executable (main.cpp is the entry point)
add_executable(AutoTune src/main.cpp src/autotune.cpp)

# Add SoundTouch as a subdirectory
add_subdirectory(SoundTouch)
add_subdirectory(AudioFile)
add_subdirectory(FFT)
# 
# Include SoundTouch headers
target_include_directories(AutoTune PRIVATE SoundTouch/include)
target_include_directories(AutoTune PRIVATE AudioFile)
target_include_directories(AutoTune PRIVATE src)
target_include_directories(AutoTune PRIVATE FFT)


# Link the SoundTouch library to your project
target_link_libraries(AutoTune PRIVATE SoundTouch)
target_link_libraries(AutoTune PRIVATE AudioFile)
target_link_libraries(AutoTune PRIVATE kissfft)
