#include "projects.h"

#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QXmlStreamReader>

#include <core/errordescription.h>
#include <core/finalizator.h>
#include <core/model/project.h>
#include <core/model/root.h>
#include "context.h"
#include "../common.h"

using namespace Core;
using namespace std;

namespace ActiveCollab
{
namespace SyncTask
{

void throwXmlError(QXmlStreamReader* xml, const QString& description)
{
    throw Error(ErrorCode::Parse, QObject::tr("%1\nLine %2, column %3")
                .arg(description)
                .arg(xml->lineNumber())
                .arg(xml->columnNumber()));
}

Projects::Projects(const ContextPtr& ctx, QObject* parent)
    : Core::BackgroundTask(tr("Refresh project list"), parent)
    , ctx_(ctx)
{
}

void Projects::doStart()
{
    auto reply = ctx_->client->get(QNetworkRequest(ctx_->getUrl("projects")));
    reply->setParent(this);
    QObject::connect(reply, &QNetworkReply::finished, this, &Projects::replyFinished);
}

void Projects::replyFinished()
{
    FINALLY { emit finished(); };
    auto reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
    try
    {
        checkReply(reply);

        QList<Model::ProjectPtr> projects;

        QXmlStreamReader xml(reply);

        QDjango::beginTransaction();
        try
        {
            if (xml.readNextStartElement())
            {
                if (xml.name() == "projects")
                {
                    while (xml.readNextStartElement())
                    {
                        if (xml.name() == "project")
                        {
                            parseProject(&xml, projects);
                        }
                        else
                            throwXmlError(&xml, QObject::tr("Unknown tag: %1").arg(xml.name().toString()));
                    }
                }
                else
                    throwXmlError(&xml, QObject::tr("Reply not a projects list."));

            }

            // remove old projects
//            for (auto p : ctx_->root->projects)
//            {
//                if (p->connectionId
//            }



            QDjango::commitTransaction();
        }
        catch (...)
        {
            QDjango::rollbackTransaction();
            throw;
        }

        if (xml.error() != QXmlStreamReader::NoError)
        {
            throw Error(ErrorCode::Parse, QObject::tr("%1\nLine %2, column %3")
                        .arg(xml.errorString())
                        .arg(xml.lineNumber())
                        .arg(xml.columnNumber()));
        }


        // remove other projects

    }
    CATCH_ERROR_IN_TASK;
}

void Projects::parseProject(QXmlStreamReader* xml, QList<Core::Model::ProjectPtr>& projects)
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

    auto project = Model::Project::get(ctx_->root->projects, id, ctx_->connectionId);
    if (!project)
    {
        project = make_shared<Model::Project>();
        project->externalId = id;
        project->connectionId = ctx_->connectionId;
    }
    project->title = name;
    if (project->isNew())
        ctx_->root->projects.addEntity(project);
    else
    {
        if (!project->save())
            throw Error(Core::ErrorCode::Database, "<59090fe7> Cannot save project");
    }

    projects.append(project);
}

}
}
