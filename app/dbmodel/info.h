#pragma once

#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace DBModel
{

// database information table
class Info : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(int dbVersion MEMBER dbVersion)
public:

    // database version
    int dbVersion;
};

}
