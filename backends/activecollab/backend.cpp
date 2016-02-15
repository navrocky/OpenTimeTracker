#include "backend.h"

#include <QIcon>

#include "connection.h"
#include "optionswidget.h"

namespace ActiveCollab
{

Backend::Backend(const Core::ApplicationContextPtr& ctx, QObject* parent)
    : Core::PMS::BackendPlugin(ctx, parent)
{
}

QString Backend::name() const
{
    return "ActiveCollab v4";
}

QString Backend::title() const
{
    return QObject::tr("activeCollab v4");
}

QIcon Backend::icon() const
{
    // TODO
    return QIcon();
}

Core::PMS::Connection* Backend::createConnection(QObject* parent) const
{
    return new Connection(applicationContext(), this, parent);
}

QWidget* Backend::createOptionsWidget(Core::PMS::Connection* connection, QWidget* parent) const
{
    auto w = new OptionsWidget(qobject_cast<Connection*>(connection), parent);
    return w;
}

}
