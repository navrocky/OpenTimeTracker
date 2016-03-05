#include "projects.h"

#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>

#include <core/errordescription.h>
#include <core/finalizator.h>
#include "context.h"
#include "../common.h"

using namespace Core;

namespace ActiveCollab
{
namespace SyncTask
{

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
        auto dom = checkReplyAndParseXml(reply);


    }
    CATCH_ERROR_IN_TASK;
}

}
}
