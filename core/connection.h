#pragma once

#include <functional>

#include <QObject>
#include <QVariantMap>
#include <QList>
#include <QDateTime>

#include "implicitsharing.h"
#include "error.h"
#include "pointers.h"

namespace Core
{

// Project Management System
namespace PMS
{

typedef std::function<void(Error)> SimpleResultHandler;

class BackendPlugin;

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(const ApplicationContextPtr& ctx, const BackendPlugin* plugin, QObject* parent);

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

    virtual BackgroundTask* sync(QObject* taskParent = 0) { return nullptr; }
    virtual bool isSyncUsed() { return false; }
    void setLastSyncDateTime(const QDateTime& );
    QDateTime lastSyncDateTime() const;

    ApplicationContextPtr applicationContext() const;

signals:
    /// Connection's options changed
    void connectionChanged();

    void validChanged();

protected:
    void setValid(bool);

private:
    DECL_DATA
};

}
}
