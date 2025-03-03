cmake_minimum_required(VERSION 3.27)
project(afx VERSION 1.0.0)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debugging
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Find external libraries
find_package(SndFile REQUIRED)
find_package(FFTW3 CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES =
    src/*.cpp
    src/effects/*.cpp
    src/effects/filters/*.cpp
)

# Add the executable with all source files
add_library(afx SHARED ${SRC_FILES})
target_include_directories(afx PUBLIC ${CMAKE_SOURCE_DIR}/include)

install(TARGETS afx
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Link external libraries
target_link_libraries(afx PRIVATE 
    SndFile::sndfile 
    FFTW3::fftw3
)
install(DIRECTORY include/ DESTINATION share/afx)