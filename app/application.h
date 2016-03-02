#pragma once

#include <memory>
#include <QObject>
#include <QPointer>
#include <QSqlDatabase>
#include <core/pointers.h>
#include <core/connection.h>
#include "pointers.h"

typedef QList<Core::PMS::BackendPluginPtr> BackendPlugins;
typedef QList<Core::PMS::ConnectionPtr> Connections;

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
    void addConnection(Core::PMS::ConnectionPtr connection)
    {
        connect(connection.get(), &Core::PMS::Connection::connectionChanged,
                this, &Application::connectionChanged);
        connections_ << connection;
        emit connectionAdded(connection);
        saveConnection(connection.get());
    }
    void removeConnection(Core::PMS::ConnectionPtr connection);

    Core::ApplicationContextPtr context() const { return ctx_; }

signals:
    void connectionAdded(Core::PMS::ConnectionPtr);
    void connectionRemoved(Core::PMS::ConnectionPtr);

private slots:
    void connectionChanged();

private:
    void initDatabase();
    int getDbVersion();
    void loadConnections();
    void saveConnection(Core::PMS::Connection* connection);

    // migrations
    void migrateFromVersion0();

    Core::PMS::BackendPluginPtr getBackendByName(const QString&);

    BackendPlugins backends_;
    Connections connections_;
    QSqlDatabase db_;
    Core::ApplicationContextPtr ctx_;
};
