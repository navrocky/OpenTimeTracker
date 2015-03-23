set(TARGET core)

set(SOURCES
    implicitsharing.h
    error.h
    error.cpp
    pmsbackend.h
    pmsbackend.cpp
    model.h
    model.cpp

    model/pointers.h
    model/root.h
    model/root.cpp
    model/project.h
    model/project.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

find_package(Qt5Core)
find_package(Qt5Sql)
target_link_libraries(${TARGET} Qt5::Core Qt5::Sql)
