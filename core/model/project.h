#pragma once

#include "remoteentity.h"

namespace Core
{
namespace Model
{

class Project : public RemoteEntity
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=project")

    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString description MEMBER description)

public:
    Project();

    QString title;
    QString description;
};

}
}
