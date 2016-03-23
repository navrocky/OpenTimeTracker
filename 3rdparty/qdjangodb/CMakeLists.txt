set(TARGET qdjangodb)

set(SOURCES
    QDjango.cpp
    QDjango.h
    QDjango_p.h
    QDjangoMetaModel.cpp
    QDjangoMetaModel.h
    QDjangoModel.cpp
    QDjangoModel.h
    QDjangoQuerySet.cpp
    QDjangoQuerySet.h
    QDjangoQuerySet_p.h
    QDjangoWhere.cpp
    QDjangoWhere.h
    QDjangoWhere_p.h
    QDjangoScopedTransaction.h
    QDjangoScopedTransaction.cpp
)

find_package(Qt5Core)
find_package(Qt5Sql)

set(CMAKE_AUTOMOC ON)

add_library(${TARGET} SHARED ${SOURCES})

target_link_libraries(${TARGET} Qt5::Core Qt5::Sql)
