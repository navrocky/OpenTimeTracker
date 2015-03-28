#pragma once

#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace Core
{
namespace Model
{

class TaskBase : public QDjangoModel
{
    Q_OBJECT

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString description MEMBER description)

public:
    QString id;
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
