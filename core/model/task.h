#pragma once

#include "remoteentity.h"

namespace Core
{
namespace Model
{

class TaskBase : public RemoteEntity
{
    Q_OBJECT
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString description MEMBER description)
public:
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
