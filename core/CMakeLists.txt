set(TARGET core)

set(SOURCES
    pmsbackend.h
    pmsbackend.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

find_package(Qt5Core)
find_package(Qt5Network)
target_link_libraries(${TARGET} Qt5::Core Qt5::Network)
