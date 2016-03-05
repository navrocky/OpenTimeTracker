set(TARGET core)

add_subdirectory(model)

set(SOURCES
    init.h
    init.cpp
    implicitsharing.h
    errorcode.h
    error.h
    error.cpp
    errordescription.h
    errordescription.cpp
    backend.h
    backend.cpp
    connection.h
    connection.cpp
    pointers.h
    optional.h
    pointerscommon.h
    applicationcontext.h
    applicationcontext.cpp
    backgroundtask.h
    backgroundtask.cpp
    finalizator.h
    finalizator.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

find_package(Qt5Core)
find_package(Qt5Sql)
target_link_libraries(${TARGET} Qt5::Core Qt5::Sql)
