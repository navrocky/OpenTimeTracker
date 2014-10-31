set(TARGET activecollabbackend)

set(SOURCES
    backend.h
    backend.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})
target_link_libraries(${TARGET} core)

find_package(Qt5Core)
find_package(Qt5Network)
target_link_libraries(${TARGET} Qt5::Core Qt5::Network)
