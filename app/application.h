#pragma once

#include <memory>
#include <QApplication>
#include <QPointer>
#include <QSqlDatabase>
#include <core/pmsbackend.h>
#include "pointers.h"

typedef QList<BackendPluginPtr> BackendPlugins;
typedef QList<ConnectionPtr> Connections;

class QSqlDatabase;

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int& argc, char** argv);

    void init();

    static Application* instance();

    BackendPlugins backends() const { return backends_; }

    template <typename T>
    void registerBackend()
    {
        backends_ << std::make_shared<T>();
    }

    Connections connections() const { return connections_; }
    void addConnection(ConnectionPtr connection);
    void removeConnection(ConnectionPtr connection);

signals:
    void connectionAdded(ConnectionPtr);
    void connectionRemoved(ConnectionPtr);

private slots:
    void connectionChanged();

private:
    void initDatabase();
    int getDbVersion();
    void loadConnections();

    // migrations
    void migrateFromVersion0();

    BackendPluginPtr getBackendByName(const QString&);

    BackendPlugins backends_;
    Connections connections_;
    QSqlDatabase db_;
};
