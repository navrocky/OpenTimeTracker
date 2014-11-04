#pragma once

#include <memory>
#include <QApplication>
#include <core/pmsbackend.h>
#include "pointers.h"

typedef QList<BackendPluginPtr> BackendPlugins;
typedef QList<ConnectionPtr> Connections;

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int& argc, char** argv);

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
    BackendPlugins backends_;
    Connections connections_;
};
