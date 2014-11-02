#pragma once

#include <functional>

#include <QObject>
#include <QVariantMap>
#include <QList>

#include "implicitsharing.h"
#include "error.h"

namespace Core
{
namespace PMS
{

#define DECL_DATA \
    struct Data; ImplicitSharing<Data> d;

typedef std::function<void(Error)> SimpleResultHandler;

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QObject* parent);

    virtual void load(const QVariantMap&) = 0;
    virtual void save(QVariantMap&) const = 0;

    QString title() const;
    void setTitle(const QString&);

    virtual void checkConnection(SimpleResultHandler) = 0;

private:
    DECL_DATA
};

class BackendPlugin : public QObject
{
    Q_OBJECT
public:
    BackendPlugin(QObject* parent = 0);

    virtual QString name() const = 0;
    virtual QString title() const = 0;
    virtual QIcon icon() const = 0;

    virtual Connection* createConnection(QObject* parent) const = 0;
    virtual QWidget* createOptionsWidget(Connection* connection, QWidget* parent) = 0;

};

}
}
