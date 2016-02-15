#pragma once

#include <QObject>

#include "connection.h"
#include "pointers.h"

namespace Core
{
namespace PMS
{

class BackendPlugin : public QObject
{
    Q_OBJECT
public:
    BackendPlugin(const ApplicationContextPtr& ctx, QObject* parent = 0);

    virtual QString name() const = 0;
    virtual QString title() const = 0;
    virtual QIcon icon() const = 0;

    virtual Connection* createConnection(QObject* parent = 0) const = 0;
    virtual QWidget* createOptionsWidget(Connection* connection, QWidget* parent = 0) const = 0;

    ApplicationContextPtr applicationContext() const { return ctx_; }

private:
    ApplicationContextPtr ctx_;
};

}
}
