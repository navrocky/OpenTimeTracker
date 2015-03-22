#pragma once

#include <QVariantMap>
#include <3rdparty/qdjangodb/QDjangoModel.h>

namespace DBModel
{

/// Connection to account
class Connection : public QDjangoModel
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=connection")

    Q_PROPERTY(QString backendName MEMBER backendName)
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QByteArray options MEMBER options)

public:
    /// Backend name
    QString backendName;

    /// User specified title
    QString title;

    /// Connection specific options
    QByteArray options;
};

}
