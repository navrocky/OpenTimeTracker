#pragma once

#include <core/backgroundtask.h>
#include <core/model/pointers.h>
#include "pointers.h"

class QXmlStreamReader;

namespace ActiveCollab
{
namespace SyncTask
{

class Tasks: public Core::BackgroundTask
{
    Q_OBJECT
public:
    Tasks(const QString& projectId, const ContextPtr& ctx, QObject* parent = 0);

protected:
    void doStart() override;

private:
    void replyFinished();
    void parseTask(QXmlStreamReader* xml, Core::Model::EntitySync<Core::Model::Task>& sync);

    ContextPtr ctx_;
    QString projectId_;
};

}
}
