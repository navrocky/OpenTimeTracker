set(TARGET core)

set(SOURCES
    implicitsharing.h
    error.h
    error.cpp
    pmsbackend.h
    pmsbackend.cpp
    model.h
    model.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

find_package(Qt5Core)
target_link_libraries(${TARGET} Qt5::Core)
