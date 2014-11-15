project(OpenTimeTracker)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR})

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(core)
add_subdirectory(app)
add_subdirectory(backends)
add_subdirectory(3rdparty)

# additional files
add_custom_target(additional SOURCES
    README.md
    project.astylerc
)
