set(TARGET activecollabbackend)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    common.h
    common.cpp
    backend.h
    backend.cpp
    connection.h
    connection.cpp
    optionswidget.h
    optionswidget.cpp

    synctask/pointers.h
    synctask/syncall.h
    synctask/syncall.cpp
    synctask/context.h
    synctask/context.cpp
    synctask/projects.h
    synctask/projects.cpp
    synctask/tasks.h
    synctask/tasks.cpp
)

set(IFACES
    optionswidget.ui
)

find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Xml)
qt5_wrap_ui(SOURCES ${IFACES})

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})
target_link_libraries(${TARGET} core)
target_link_libraries(${TARGET} Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets Qt5::Xml)
