#include "tasks.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QLoggingCategory>

#include <3rdparty/qdjangodb/QDjangoScopedTransaction.h>

#include <core/model/task.h>
#include <core/errordescription.h>
#include <core/finalizator.h>
#include <core/model/project.h>
#include <core/model/root.h>
#include <core/model/entitysync.h>
#include "context.h"
#include "../common.h"

Q_LOGGING_CATEGORY(LOGGER, "ActiveCollab::SyncTask::Tasks")

using namespace Core;

namespace ActiveCollab
{
namespace SyncTask
{

Tasks::Tasks(const QString& projectId, const ContextPtr& ctx, QObject* parent)
    : Core::BackgroundTask(tr("Get tasks for project %1").arg(projectId), parent)
    , ctx_(ctx)
    , projectId_(projectId)
{
}

void Tasks::doStart()
{
    qCDebug(LOGGER) << tr("Tasks synchronization for project %1 started").arg(projectId_);
    auto reply = ctx_->client->get(QNetworkRequest(ctx_->getUrl(QString("projects/%1/tasks").arg(projectId_))));
    reply->setParent(this);
    QObject::connect(reply, &QNetworkReply::finished, this, &Tasks::replyFinished);
}

void Tasks::replyFinished()
{
    FINALLY { emit finished(); };
    auto reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
    try
    {
        checkReply(reply);

        QXmlStreamReader xml(reply);

        auto project = Model::Project::tryGetByExtId(ctx_->root->projects.entities(), projectId_, ctx_->connectionId);

        Model::EntitySync<Model::Task> sync(project->tasks(), ctx_->connectionId);

        QDjangoScopedTransaction transaction;
        if (xml.readNextStartElement())
        {
            if (xml.name() == "tasks")
            {
                while (xml.readNextStartElement())
                {
                    if (xml.name() == "task")
                    {
                        parseTask(&xml, sync);
                    }
                    else
                        throwXmlError(&xml, QObject::tr("Unknown tag: %1").arg(xml.name().toString()));
                }
            }
            else
                throwXmlError(&xml, QObject::tr("Reply not a tasks list."));

        }
        sync.removeOutdated();
        transaction.commit();

        if (xml.error() != QXmlStreamReader::NoError)
        {
            throw Error(ErrorCode::Parse, QObject::tr("%1\nLine %2, column %3")
                        .arg(xml.errorString())
                        .arg(xml.lineNumber())
                        .arg(xml.columnNumber()));
        }
    }
    CATCH_ERROR_IN_TASK;
}

void Tasks::parseTask(QXmlStreamReader* xml, Core::Model::EntitySync<Core::Model::Task>& sync)
{
    QString id;
    QString name;

    while (xml->readNextStartElement())
    {
        if (xml->name() == "id")
            id = xml->readElementText();
        else if (xml->name() == "name")
            name = xml->readElementText();
        else
            xml->skipCurrentElement();
    }

    auto task = sync.get(id);
    task->title = name;
    task->projectId = projectId_.toInt();
    sync.release(task);

}

}
}
