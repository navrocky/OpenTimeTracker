#include "connection.h"

#include <QPointer>

#include "backend.h"

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

    int id;
    QString title;
    QPointer<const BackendPlugin> plugin;
    bool valid;
};

Connection::Connection(const BackendPlugin* plugin, QObject* parent)
    : QObject(parent)
{
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

void Connection::setValid(bool v)
{
    if (d->valid == v)
        return;
    d->valid = v;
    emit validChanged();
}

}
}
