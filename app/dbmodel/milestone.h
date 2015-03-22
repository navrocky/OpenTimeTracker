#pragma once

#include <QString>
#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace DBModel
{

class Milestone : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=milestone")

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString title MEMBER title)

public:
    QString id;
    QString title;
};

}
