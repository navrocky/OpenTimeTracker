#include "connection.h"

#include <QPointer>

#include <3rdparty/qdjangodb/QDjangoQuerySet.h>

#include "model/connection.h"
#include "backend.h"
#include "error.h"

namespace Core
{
namespace PMS
{

struct Connection::Data
{
    Data()
        : id(0)
        , valid(false)
    {}

    ApplicationContextPtr ctx;
    int id;
    QString title;
    QPointer<const BackendPlugin> plugin;
    bool valid;
    QDateTime lastSyncDateTime;
};

Connection::Connection(const ApplicationContextPtr& ctx, const BackendPlugin* plugin, QObject* parent)
    : QObject(parent)
{
    d->ctx = ctx;
    d->plugin = plugin;
}

const BackendPlugin* Connection::plugin() const
{
    return d->plugin;
}

int Connection::id() const
{
    return d->id;
}

void Connection::setId(int s)
{
    d->id = s;
}

QString Connection::title() const
{
    return d->title;
}

void Connection::setTitle(const QString& v)
{
    d->title = v;
}

bool Connection::isValid() const
{
    return d->valid;
}

void Connection::setLastSyncDateTime(const QDateTime& value)
{
    d->lastSyncDateTime = value;
    emit connectionChanged();
}

QDateTime Connection::lastSyncDateTime() const
{
    return d->lastSyncDateTime;
}

ApplicationContextPtr Connection::applicationContext() const
{
    return d->ctx;
}

void Connection::setValid(bool v)
{
    if (d->valid == v)
        return;
    d->valid = v;
    emit validChanged();
}

}
}
