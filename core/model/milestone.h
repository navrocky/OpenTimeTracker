#pragma once

#include <QString>
#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace Core
{
namespace Model
{

class Milestone : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=milestone")
    Q_CLASSINFO("id", "primary_key=true")

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString title MEMBER title)

public:
    QString id;
    QString title;
};

}
}
