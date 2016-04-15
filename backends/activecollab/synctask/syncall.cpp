#include "syncall.h"

#include <QNetworkAccessManager>

#include <core/model/root.h>
#include <core/backgroundtask.h>

#include "projects.h"
#include "tasks.h"
#include "context.h"

namespace ActiveCollab
{
namespace SyncTask
{

SyncAll::SyncAll(const ContextPtr& ctx, QObject* parent)
    : Core::BackgroundTask(tr("ActiveCollab v4 connection synchronization"), parent)
    , ctx_(ctx)
{
}

void SyncAll::doStart()
{
    auto task = new Projects(ctx_, this);
    ctx_->taskManager->startDetached(task);
    connect(task, &Projects::finished, [this]()
    {
        auto parallelTask = new Core::ParallelBackgroundTask(tr("Update tasks"), this);
        for (auto project : ctx_->root->projects.entities())
        {
            parallelTask->addTask(new SyncTask::Tasks(project->externalId, ctx_));
        }
        ctx_->taskManager->startDetached(parallelTask);
        connect(parallelTask, &BackgroundTask::finished, [this]()
        {
            finish();
        });
    });
}

}
}
