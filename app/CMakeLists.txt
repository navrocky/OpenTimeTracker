set(TARGET opentimetracker)

cmake_policy(SET CMP0020 NEW)
if(POLICY CMP0028)
    cmake_policy(SET CMP0028 NEW)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(dbmodel)

set(SOURCES
    pointers.h
    dbtools.h
    dbtools.cpp
    main.cpp
    application.h
    application.cpp
    mainwindow.h
    mainwindow.cpp
    optionsdialog.h
    optionsdialog.cpp
    createaccountpage.h
    createaccountpage.cpp
)

set(IFACES
    mainwindow.ui
    optionsdialog.ui
    createaccountpage.ui
)

set(RESOURCES
    #resources.qrc
)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Sql)
find_package(Qt5Xml)

qt5_wrap_ui(SOURCES ${IFACES})
qt5_add_resources(SOURCES ${RESOURCES})

set(CMAKE_AUTOMOC ON)

add_executable(${TARGET} WIN32 ${SOURCES})

target_link_libraries(${TARGET}
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::Sql
    Qt5::Xml

    core
    activecollabbackend
    app_dbmodel
    qdjangodb
)
