#pragma once

#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace Core
{
namespace Model
{

/// Database information table
class Info : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=info")
    Q_PROPERTY(int dbVersion MEMBER dbVersion)
public:
    Info();

    /// database version
    int dbVersion;
};

}
}
