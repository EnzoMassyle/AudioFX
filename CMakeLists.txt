cmake_minimum_required(VERSION 3.27)
project(afx VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DPLATFORM_MACOS)
elseif(UNIX)
    add_definitions(-DPLATFORM_LINUX)
endif()

# Find external libraries
find_package(FFTW3 CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES =
src/*.cpp
src/effects/*.cpp
src/effects/filters/*.cpp
)

# Add the executable with all source files
add_library(afx ${SRC_FILES})
target_include_directories(afx 
PUBLIC 
$<INSTALL_INTERFACE:include>
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_compile_features(afx PRIVATE cxx_std_17)
install(TARGETS afx
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Link external libraries
target_link_libraries(afx 
    PUBLIC 
    SndFile::sndfile 
    FFTW3::fftw3
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_DATADIR}/cmake/AFX)


install(TARGETS afx
    EXPORT afx-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(afx PROPERTIES EXPORT_NAME AFX)
install(DIRECTORY ${CMAKE_SOURCE_DIR} include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR} assets/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# install(
#     DIRECTORY ${CMAKE_SOURCE_DIR} include/  # Ensure it matches your structure
#     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#     CONFIGURATIONS Debug Releases
# )

install(EXPORT afx-targets
    FILE
        afxTargets.cmake
    NAMESPACE
        AFX::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/AFXConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/afxConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/afxConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/afxConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/afxConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT afx-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/afxTargets.cmake
    NAMESPACE AFX::)

export(PACKAGE AFX)
# message(STATUS "AFX Headers will be installed to: ${CMAKE_INSTALL_INCLUDEDIR}")

