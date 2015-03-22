#pragma once

#include <QString>
#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace DBModel
{

class Project : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=project")

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString title MEMBER title)

public:
    QString id;
    QString title;
};

}
