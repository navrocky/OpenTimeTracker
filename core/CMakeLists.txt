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
    model/common.h
    model/tools.h
    model/tools.cpp
    model/root.h
    model/root.cpp
    model/project.h
    model/project.cpp
    model/milestone.h
    model/milestone.cpp
    model/task.h
    model/task.cpp
    model/user.h
    model/user.cpp
    model/connection.h
    model/connection.cpp
    model/priority.h
    model/priority.cpp
    model/category.h
    model/category.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

find_package(Qt5Core)
find_package(Qt5Sql)
target_link_libraries(${TARGET} Qt5::Core Qt5::Sql)
