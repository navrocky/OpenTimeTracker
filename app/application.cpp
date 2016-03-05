#include "application.h"

#include <functional>
#include <QMap>
#include <QVariantMap>
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
#include <core/backend.h>
#include <core/applicationcontext.h>
#include <core/model/modelregistration.h>
#include <core/model/info.h>
#include <core/model/connection.h>
#include <core/backgroundtask.h>
#include "dbtools.h"

using namespace std;

Q_LOGGING_CATEGORY(APPLICATION, "Application")

static Application* application = 0;

Application::Application(QObject* parent)
    : QObject(parent)
{
    application = this;
    ctx_ = make_shared<Core::ApplicationContext>();
    ctx_->taskManager = new Core::TaskManager(this);
}

Application::~Application()
{
    application = 0;
}

void Application::init()
{
    initDatabase();
    loadConnections();
}

Application* Application::instance()
{
    return application;
}



void Application::removeConnection(Core::PMS::ConnectionPtr connection)
{
    disconnect(connection.get(), &Core::PMS::Connection::connectionChanged,
               this, &Application::connectionChanged);
    connections_.removeAll(connection);
    emit connectionRemoved(connection);
}

void Application::connectionChanged()
{
    auto connection = qobject_cast<Core::PMS::Connection*>(sender());
    saveConnection(connection);
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

    Core::Model::registerModels();
    QDjango::setDatabase(db_);
    QDjango::setDebugEnabled(true);

    typedef QMap<int, std::function<void()>> Migrations;
    Migrations migrations;

    // register migrations here
    migrations[0] = std::bind(&Application::migrateFromVersion0, this);

    // execute migrations
    forever
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
    QDjangoQuerySet<Core::Model::Info> info;
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
    QDjangoQuerySet<Core::Model::Connection> conns;
    for (const Core::Model::Connection& conn: conns)
    {
        try
        {
            Core::PMS::BackendPluginPtr backend = getBackendByName(conn.backendName);
            if (!backend)
                throw Core::Error(tr("Connection backend not found: %1").arg(conn.backendName));
            auto connection = Core::PMS::ConnectionPtr(backend->createConnection());

            connect(connection.get(), &Core::PMS::Connection::connectionChanged,
                    this, &Application::connectionChanged);

            connection->setId(conn.pk().toInt());
            connection->setTitle(conn.title);
            connection->setLastSyncDateTime(conn.lastSyncDateTime);

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

void Application::saveConnection(Core::PMS::Connection* connection)
{
    bool newConnection = connection->id() == 0;

    Core::Model::Connection conn;
    if (!newConnection)
        conn.setPk(connection->id());
    conn.backendName = connection->plugin()->name();
    conn.title = connection->title();
    conn.lastSyncDateTime = connection->lastSyncDateTime();

    QVariantMap m;
    connection->save(m);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream ds(&buf);
    ds << m;
    conn.options = buf.data();
    if (!conn.save())
        throw Core::Error(tr("Cannot save connection to DB"));
    if (newConnection)
        connection->setId(conn.pk().toInt());
}

void Application::migrateFromVersion0()
{
    if (!QDjango::createTables())
        throw Core::Error(tr("Cannot create DB tables"));

    Core::Model::Info info;
    info.dbVersion = 1;
    if (!info.save())
        throw Core::Error(tr("Cannot save DB version"));
}

Core::PMS::BackendPluginPtr Application::getBackendByName(const QString& name)
{
    for (const auto& backend: backends_)
    {
        if (backend->name() == name)
            return backend;
    }
    return Core::PMS::BackendPluginPtr();
}
