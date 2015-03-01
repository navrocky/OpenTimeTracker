#include "application.h"

#include <functional>
#include <QMap>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLoggingCategory>
#include <QStandardPaths>
#include <QDir>
#include <QBuffer>
#include <QDataStream>

#include <3rdparty/qdjangodb/QDjango.h>
#include <3rdparty/qdjangodb/QDjangoQuerySet.h>
#include <core/error.h>
#include <core/pmsbackend.h>
#include "dbmodel/modelregistration.h"
#include "dbmodel/info.h"
#include "dbmodel/connection.h"
#include "dbtools.h"

Q_LOGGING_CATEGORY(APPLICATION, "application")

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
{

}

void Application::init()
{
    initDatabase();
    loadConnections();
}

Application* Application::instance()
{
    return static_cast<Application*>(QApplication::instance());
}

void Application::addConnection(ConnectionPtr connection)
{
    connections_ << connection;
    emit connectionAdded(connection);

    DBModel::Connection conn;
    conn.name = connection->plugin()->name();
    conn.title = connection->title();

    QVariantMap m;
    connection->save(m);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream ds(&buf);
    ds << m;
    conn.options = buf.data();
    if (!conn.save())
        throw Core::Error(tr("Cannot save connection to DB"));
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

    typedef QMap<int, std::function<void()>> Migrations;
    Migrations migrations;

    // register migrations here
    migrations[0] = std::bind(&Application::migrateFromVersion0, this);

    // execute migrations
    while (true)
    {
        int dbVersion = getDbVersion();
        if (migrations.contains(dbVersion))
        {
            qCDebug(APPLICATION) << tr("Migrate DB from version: %1").arg(dbVersion).toUtf8().data();
            migrations[dbVersion]();
        }
        else
            break;
    }
    qCDebug(APPLICATION) << tr("Current DB version: %1").arg(getDbVersion()).toUtf8().data();
}

int Application::getDbVersion()
{
    QDjangoQuerySet<DBModel::Info> info;
    if (info.count() == 1)
    {
        auto it = info.begin();
        return it->dbVersion;
    }
    else
        return 0;
}

void Application::loadConnections()
{
    QDjangoQuerySet<DBModel::Connection> conns;
    for (const DBModel::Connection& conn: conns)
    {
        try
        {
            BackendPluginPtr backend = getBackendByName(conn.name);
            if (!backend)
                throw Core::Error(tr("Connection backend not found: %1").arg(conn.name));
            auto connection = ConnectionPtr(backend->createConnection());

            connect(connection, &Core::PMS::Connection::changed)

            QBuffer buf;
            buf.setData(conn.options);
            buf.open(QBuffer::ReadOnly);
            QDataStream ds(&buf);
            QVariantMap m;
            ds >> m;
            connection->load(m);

            connections_ << connection;
        }
        CATCH_ERROR(APPLICATION)
    }
}

void Application::migrateFromVersion0()
{
    if (!QDjango::createTables())
        throw Core::Error(tr("Cannot create DB tables"));

    DBModel::Info info;
    info.dbVersion = 1;
    if (!info.save())
        throw Core::Error(tr("Cannot save DB version"));
}

BackendPluginPtr Application::getBackendByName(const QString& name)
{
    for (const BackendPluginPtr& backend: backends_)
    {
        if (backend->name() == name)
            return backend;
    }
    return BackendPluginPtr();
}
