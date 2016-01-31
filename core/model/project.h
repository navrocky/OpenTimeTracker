#pragma once

#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace Core
{
namespace Model
{

class Project : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=project")
    Q_CLASSINFO("id", "primary_key=true")

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString description MEMBER description)
    Q_PROPERTY(int connectionId MEMBER connectionId)

public:
    Project();

    QString id;
    QString title;
    QString description;
    int connectionId;
};

}
}
