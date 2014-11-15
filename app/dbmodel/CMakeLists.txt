set(TARGET app_dbmodel)

set(SOURCES
    modelregistration.h
    modelregistration.cpp
    info.h
    info.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} ${SOURCES})

find_package(Qt5Core)
find_package(Qt5Sql)
target_link_libraries(${TARGET}
    Qt5::Core
    Qt5::Sql
    qdjangodb
)
