cmake_minimum_required(VERSION 3.27)
project(fxaudio VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(ANDROID)
    add_definitions(-DPlATFORM_ANDROID)
elseif(APPLE)
    add_definitions(-DPLATFORM_MACOS)
elseif(UNIX)
    add_definitions(-DPLATFORM_LINUX)
endif()

# Find external libraries
find_package(FFTW3 CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)


file(GLOB_RECURSE SRC_FILES =
src/effects/*.cpp
src/effects/filters/*.cpp
)

enable_testing()


add_library(fxaudio ${SRC_FILES})
# add_executable(fxaudio ${SRC_FILES} src/main.cpp)
target_include_directories(fxaudio 
PUBLIC 
$<INSTALL_INTERFACE:include>
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)




target_compile_features(fxaudio PRIVATE cxx_std_17)
install(TARGETS fxaudio
ARCHIVE DESTINATION lib
LIBRARY DESTINATION lib
RUNTIME DESTINATION bin
)


# Link external libraries
target_link_libraries(fxaudio 
PUBLIC 
SndFile::sndfile 
FFTW3::fftw3
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_DATADIR}/cmake/FXAUDIO)


install(TARGETS fxaudio
EXPORT fxaudio-targets
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR} include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


install(EXPORT fxaudio-targets
    FILE
        fxaudioTargets.cmake
    NAMESPACE
        FXAUDIO::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/fxaudioConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/fxaudioConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/fxaudioConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/fxaudioConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/fxaudioConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT fxaudio-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/fxaudioTargets.cmake
    NAMESPACE FXAUDIO::)

export(PACKAGE FXAUDIO)


# TESTING 

enable_testing()

# Gather test files (modify this to include your test files)
file(GLOB_RECURSE TEST_FILES 
tests/*.cpp
)
message(STATUS "${TEST_FILES}")

# Create test executable
add_executable(fxaudio_tests ${TEST_FILES} ${SRC_FILES} tests/main.cpp)
target_link_libraries(fxaudio_tests 
    PRIVATE 
    SndFile::sndfile 
    FFTW3::fftw3
    GTest::gtest 
    GTest::gtest_main
    GTest::gmock 
    GTest::gmock_main
)

# Register the tests with CTest
include(GoogleTest)
gtest_discover_tests(fxaudio_tests)

