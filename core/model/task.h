#pragma once

#include "remoteentity.h"

namespace Core
{
namespace Model
{

class TaskBase : public RemoteEntity
{
    Q_OBJECT

    Q_CLASSINFO("projectId", "db_column=project")
    Q_PROPERTY(int projectId MEMBER projectId)

    Q_CLASSINFO("title", "db_column=title")
    Q_PROPERTY(QString title MEMBER title)

    Q_CLASSINFO("description", "db_column=description")
    Q_PROPERTY(QString description MEMBER description)
public:
    int projectId;
    QString title;
    QString description;
};

class Task : public TaskBase
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=task")
public:

};

}
}
