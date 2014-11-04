#include "pmsbackend.h"

#include <QPointer>

namespace Core
{
namespace PMS
{

////////////////////////////////////////////////////////////////////////////////

struct Connection::Data
{
    QString title;
    QPointer<const BackendPlugin> plugin;
};

Connection::Connection(const BackendPlugin *plugin, QObject *parent)
    : QObject(parent)
{
    d->plugin = plugin;
}

const BackendPlugin *Connection::plugin() const
{
    return d->plugin;
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
