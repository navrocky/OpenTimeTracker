set(TARGET qt-qml-tricks)

set(SOURCES
    qqmlhelpers.cpp
    qqmlhelpers.h
    qqmlmodels.h
    qqmlobjectlistmodel.cpp
    qqmlobjectlistmodel.h
#    qqmlsvgiconhelper.cpp
#    qqmlsvgiconhelper.h
    qqmlvariantlistmodel_p.h
    qqmlvariantlistmodel.cpp
    qqmlvariantlistmodel.h
#    qquickpolygon.cpp
#    qquickpolygon.h
    qtbitstream.h
    qtcobs.h
    qtjsonpath.h
)

find_package(Qt5Core)
#find_package(Qt5Gui)
#find_package(Qt5Qml)
#find_package(Qt5Quick)
#find_package(Qt5Svg)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

target_link_libraries(${TARGET}
    Qt5::Core
#    Qt5::Gui
#    Qt5::Qml
#    Qt5::Quick
#    Qt5::Svg
    )
