#include "application.h"

#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLoggingCategory>
#include <QStandardPaths>
#include <QDir>
#include <core/error.h>

#include "dbtools.h"
#include <3rdparty/qdjangodb/QDjango.h>
#include "dbmodel/modelregistration.h"

Q_LOGGING_CATEGORY(APPLICATION, "application")

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
{

}

void Application::init()
{
    initDatabase();
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

void Application::initDatabase()
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if (!QDir().mkpath(dataPath))
        throw Core::Error(tr("Cannot create directory: %1").arg(dataPath));

    QString dbFilePath = dataPath + "/opentimetracker.sqlite";
    qCDebug(APPLICATION) << tr("Database located: %1").arg(dbFilePath).toUtf8().data();

    db_ = QSqlDatabase::addDatabase("QSQLITE");
    if (!db_.isValid())
        throw Core::Error(tr("Cannot create sqlite database connection"));
    db_.setDatabaseName(dbFilePath);
    if (!db_.open())
        throw Core::Error(tr("Cannot open sqlite database at \"%1\"").arg(dbFilePath));

    DBModel::registerModels();
    QDjango::setDatabase(db_);
    QDjango::setDebugEnabled(true);
    if (!QDjango::createTables())
        throw Core::Error(tr("Cannot create tables in database"));
}
