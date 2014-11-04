#include "application.h"

#include <QSettings>

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
{

}

Application* Application::instance()
{
    return static_cast<Application*>(QApplication::instance());
}

void Application::addConnection(ConnectionPtr connection)
{
    connections_ << connection;
    emit connectionAdded(connection);

    // save connection
    QSettings s;

    s.beginWriteArray("connections");
    s.setArrayIndex(connections_.size() - 1);



    s.endArray();
}

void Application::removeConnection(ConnectionPtr connection)
{
    connections_.removeAll(connection);
    emit connectionRemoved(connection);
}

void Application::connectionChanged()
{
    QSettings s;
}
