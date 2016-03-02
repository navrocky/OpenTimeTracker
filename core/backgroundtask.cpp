#include "backgroundtask.h"

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
}

void TaskManager::startDetached(BackgroundTask* task)
{
    if (!task->parent())
        task->setParent(this);
    connect(task, &BackgroundTask::finished, task, &BackgroundTask::deleteLater);
    task->start();
}

void TaskManager::taskFinished()
{
    updateBusyState();
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
    emit busyChanged(busy_);
}

////////////////////////////////////////////////////////////////////////////////

BackgroundTask::BackgroundTask(QObject* parent)
    : QObject(parent)
    , state_(NotStarted)
{
}

void BackgroundTask::start()
{
    doStart();
    setState(Executing);
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

ParallelBackgroundTask::ParallelBackgroundTask(QObject* parent)
    : BackgroundTask(parent)
{
}

void ParallelBackgroundTask::addTask(BackgroundTask* t)
{
    tasks_.append(t);
}

void ParallelBackgroundTask::doStart()
{
    for (auto task: tasks_)
    {
        if (task->state() == NotStarted)
            task->start();
        connect(task, &BackgroundTask::finished, this, &ParallelBackgroundTask::taskFinished);
    }
    executingTasks_ = tasks_.size();
}

void ParallelBackgroundTask::taskFinished()
{
    executingTasks_--;
    if (executingTasks_ == 0)
        emit finished();
}

}
