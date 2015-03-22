#pragma once

#include <QString>
#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace DBModel
{

class Task : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=task")

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString parentTaskId MEMBER parentTaskId)
    Q_PROPERTY(QString title MEMBER title)

public:
    QString id;
    QString parentTaskId;
    QString title;
};

}
