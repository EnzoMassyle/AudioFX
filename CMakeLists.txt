cmake_minimum_required(VERSION 3.12)
project(mc VERSION 1.0.0)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debugging
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Find external libraries
find_package(SndFile REQUIRED)
find_package(FFTW3 CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES 
    src/*.cpp
    src/effects/*.cpp
    src/headers/freeverb/Components/*.cpp  # Include all freeverb component .cpp files
)
# Add the executable with all source files
add_executable(mc ${SRC_FILES})

# Include paths for header files
target_include_directories(mc PRIVATE 
    src                      # Include the src/ directory
    src/effects              # Include the src/effects/ directory
    src/effects/filters      # Include the src/effects/filters/ directory, if needed
    src/headers
    src/headers/freeverb/Components
)

# Link external libraries
target_link_libraries(mc PRIVATE 
    SndFile::sndfile 
    FFTW3::fftw3
)
