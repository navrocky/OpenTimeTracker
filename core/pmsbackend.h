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

typedef std::function<void(Error)> SimpleResultHandler;

class BackendPlugin;

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(const BackendPlugin* plugin, QObject* parent);

    /// Reference to backend
    const BackendPlugin* plugin() const;

    /// Loading connection
    virtual void load(const QVariantMap&) = 0;

    /// Saving connection
    virtual void save(QVariantMap&) const = 0;

    /// Unique connection ID
    int id() const;
    void setId(int);

    /// Connection optional title
    QString title() const;

    /// Change connection optional title
    void setTitle(const QString&);

    /// Is connection valid?
    bool isValid() const;

signals:
    /// Connection's options changed
    void connectionChanged();

    void validChanged();

protected:
    void setValid(bool);

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

    virtual Connection* createConnection(QObject* parent = 0) const = 0;
    virtual QWidget* createOptionsWidget(Connection* connection, QWidget* parent = 0) const = 0;

};

}
}
