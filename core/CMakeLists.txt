set(TARGET core)

add_subdirectory(model)

set(SOURCES
    implicitsharing.h
    error.h
    error.cpp
    backend.h
    backend.cpp
    connection.h
    connection.cpp
    pointers.h
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

find_package(Qt5Core)
find_package(Qt5Sql)
target_link_libraries(${TARGET} Qt5::Core Qt5::Sql)
