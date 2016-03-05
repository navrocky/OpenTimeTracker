#include "backgroundtask.h"

#include <QLoggingCategory>

#include "errordescription.h"

Q_LOGGING_CATEGORY(TASK_MANAGER, "TaskManager")

namespace Core
{

TaskManager::TaskManager(QObject* parent)
    : QObject(parent)
    , busy_(false)
{
}

void TaskManager::add(BackgroundTask* task)
{
    tasks_.append(task);
    connect(task, &BackgroundTask::stateChanged, this, &TaskManager::taskStateChanged);
    connect(task, &BackgroundTask::finished, this, &TaskManager::taskFinished);
    connect(task, &BackgroundTask::destroyed, this, &TaskManager::taskDestroyed);
}

void TaskManager::updateBusyState()
{
    bool busy = false;
    for (auto task : tasks_)
    {
        if (task->state() == BackgroundTask::Executing)
        {
            busy = true;
            break;
        }
    }
    setBusy(busy);
}

void TaskManager::start(BackgroundTask* task)
{
    add(task);
    task->start();
    updateBusyState();
}

void TaskManager::startDetached(BackgroundTask* task, bool showError)
{
    if (!task->parent())
        task->setParent(this);
    connect(task, &BackgroundTask::finished, task, &BackgroundTask::deleteLater);
    if (showError)
    {
        task->setOptions(task->options() | BackgroundTask::ShowError);
    }
    start(task);
}

void TaskManager::taskStateChanged()
{
    updateBusyState();
}

void TaskManager::taskFinished()
{
    updateBusyState();
    auto task = qobject_cast<BackgroundTask*>(sender());
    if (task->error() && task->options().testFlag(BackgroundTask::ShowError))
    {
        qCCritical(TASK_MANAGER()) << task->error()->message();
        emit showTaskError(task->error());
    }
}

void TaskManager::taskDestroyed(QObject* o)
{
    auto task = static_cast<BackgroundTask*>(o);
    tasks_.removeAll(task);
    updateBusyState();
}

void TaskManager::setBusy(bool v)
{
    if (busy_ == v)
        return;
    busy_ = v;
    qCDebug(TASK_MANAGER) << "Busy:" << busy_;
    emit busyChanged(busy_);
}

////////////////////////////////////////////////////////////////////////////////

BackgroundTask::BackgroundTask(const QString& title, QObject* parent)
    : QObject(parent)
    , title_(title)
    , state_(NotStarted)
{
}

void BackgroundTask::start()
{
    doStart();
    setState(Executing);
}

void BackgroundTask::setError(const ErrorDescriptionPtr& error)
{
    errorDescription_ = error;
}

void BackgroundTask::finish()
{
    setState(Finished);
}

void BackgroundTask::setState(BackgroundTask::State state)
{
    if (state_ == state)
        return;
    state_ = state;
    emit stateChanged();
    if (state_ == Finished)
        emit finished();
}

////////////////////////////////////////////////////////////////////////////////

ParallelBackgroundTask::ParallelBackgroundTask(const QString& title, QObject* parent)
    : BackgroundTask(title, parent)
{
}

void ParallelBackgroundTask::addTask(BackgroundTask* t)
{
    tasks_.append(t);
}

void ParallelBackgroundTask::doStart()
{
    executingTasks_ = tasks_.size();
    for (auto task: tasks_)
    {
        if (task->state() == NotStarted)
            task->start();
        connect(task, &BackgroundTask::finished, this, &ParallelBackgroundTask::taskFinished);
    }
}

void ParallelBackgroundTask::taskFinished()
{
    auto task = qobject_cast<BackgroundTask*>(sender());
    if (task->error())
    {
        auto e = error();
        if (!e)
        {
            e = ErrorDescription::create(ErrorCode::Unclassified, tr("%1: task failed").arg(title()));
            setError(e);
        }
        e->addInnerError(task->error());
    }

    executingTasks_--;
    if (executingTasks_ == 0)
        emit finished();
}

}
