#pragma once

#include <QObject>
#include <core/backend.h>
#include <core/pointers.h>

namespace ActiveCollab
{

class Backend : public Core::PMS::BackendPlugin
{
    Q_OBJECT
public:
    Backend(const Core::ApplicationContextPtr& ctx, QObject* parent = 0);

    QString name() const override;
    QString title() const override;
    QIcon icon() const override;

    Core::PMS::Connection* createConnection(QObject* parent = 0) const override;
    QWidget* createOptionsWidget(Core::PMS::Connection* connection, QWidget* parent = 0) const override;

};

}
