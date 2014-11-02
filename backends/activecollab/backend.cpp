#include "backend.h"

#include <QIcon>

#include "connection.h"

namespace ActiveCollab
{

Backend::Backend(QObject *parent)
    : Core::PMS::BackendPlugin(parent)
{
}

QString Backend::name() const
{
    return "ActiveCollab";
}

QString Backend::title() const
{
    return QObject::tr("activeCollab");
}

QIcon Backend::icon() const
{
    // TODO
    return QIcon();
}

Core::PMS::Connection *Backend::createConnection(QObject *parent) const
{
    return new Connection(parent);
}

QWidget *Backend::createOptionsWidget(Core::PMS::Connection *connection, QWidget *parent)
{

}

}
