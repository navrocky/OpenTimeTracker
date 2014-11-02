#include "pmsbackend.h"

namespace Core
{
namespace PMS
{

////////////////////////////////////////////////////////////////////////////////

struct Connection::Data
{
    QString title;
};

Connection::Connection(QObject *parent)
    : QObject(parent)
{
}

QString Connection::title() const
{
    return d->title;
}

void Connection::setTitle(const QString &v)
{
    d->title = v;
}

////////////////////////////////////////////////////////////////////////////////

BackendPlugin::BackendPlugin(QObject *parent)
    : QObject(parent)
{
}

}
}
