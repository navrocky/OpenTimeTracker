set(TARGET opentimetracker)

cmake_policy(SET CMP0020 NEW)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
)

set(IFACES
    mainwindow.ui
)

set(RESOURCES
    #resources.qrc
)

find_package(Qt5Core)
find_package(Qt5Widgets)
qt5_wrap_ui(SOURCES ${IFACES})
qt5_add_resources(SOURCES ${RESOURCES})

set(CMAKE_AUTOMOC ON)

add_executable(${TARGET} WIN32 ${SOURCES})

target_link_libraries(${TARGET}
    core
    activecollabbackend
)
target_link_libraries(${TARGET} Qt5::Core Qt5::Widgets)
