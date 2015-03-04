#pragma once

#include <QVariantMap>
#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace DBModel
{

class Connection : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=connection")
    Q_CLASSINFO("name", "primary_key=true")

    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QByteArray options MEMBER options)

public:
    /// Backend name
    QString name;

    /// User specified title
    QString title;

    /// Connection specific options
    QByteArray options;

};



}
