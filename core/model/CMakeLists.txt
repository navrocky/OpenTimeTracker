set(TARGET core_model)

set(SOURCES
    pointers.h
    common.h
    tools.h
    tools.cpp
    entitylist.h
    remoteentity.h
    remoteentity.cpp
    root.h
    root.cpp
    info.h
    info.cpp
    project.h
    project.cpp
    milestone.h
    milestone.cpp
    task.h
    task.cpp
    user.h
    user.cpp
    connection.h
    connection.cpp
    priority.h
    priority.cpp
    category.h
    category.cpp
    modelregistration.h
    modelregistration.cpp
    entitysync.h
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

find_package(Qt5Core)
find_package(Qt5Sql)
target_link_libraries(${TARGET}
    Qt5::Core
    Qt5::Sql
    qdjangodb
    qt-qml-tricks
)
