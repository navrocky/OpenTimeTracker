#pragma once

#include <memory>
#include <QObject>
#include <QPointer>
#include <QSqlDatabase>
//#include <core/pmsbackend.h>
#include "pointers.h"
#include <core/pointers.h>

typedef QList<BackendPluginPtr> BackendPlugins;
typedef QList<ConnectionPtr> Connections;

class QSqlDatabase;

class Application : public QObject
{
    Q_OBJECT
public:
    Application(QObject* parent = 0);
    ~Application();

    void init();

    static Application* instance();

    BackendPlugins backends() const { return backends_; }

    template <typename T>
    void registerBackend()
    {
        backends_ << std::make_shared<T>(ctx_);
    }

    Connections connections() const { return connections_; }
    void addConnection(ConnectionPtr connection);
    void removeConnection(ConnectionPtr connection);

    Core::ApplicationContextPtr context() const { return ctx_; }

signals:
    void connectionAdded(ConnectionPtr);
    void connectionRemoved(ConnectionPtr);

private slots:
    void connectionChanged();

private:
    void initDatabase();
    int getDbVersion();
    void loadConnections();
    void saveConnection(Core::PMS::Connection* connection);

    // migrations
    void migrateFromVersion0();

    BackendPluginPtr getBackendByName(const QString&);

    BackendPlugins backends_;
    Connections connections_;
    QSqlDatabase db_;
    Core::ApplicationContextPtr ctx_;
};
