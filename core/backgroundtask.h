#pragma once

#include <QObject>
#include <QList>
#include "pointers.h"

namespace Core
{

class TaskManager: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)

public:
    explicit TaskManager(QObject* parent = 0);
    void start(BackgroundTask* task);
    void startDetached(BackgroundTask* task);

    bool isBusy() const { return busy_; }

signals:
    void busyChanged(bool);

private slots:
    void taskFinished();
    void taskDestroyed(QObject*);

private:
    void setBusy(bool);
    void add(BackgroundTask* task);
    void updateBusyState();

    QList<BackgroundTask*> tasks_;
    bool busy_;
};

class BackgroundTask: public QObject
{
    Q_OBJECT
public:
    enum State
    {
        NotStarted,
        Executing,
        Finished
    };

    BackgroundTask(QObject* parent = 0);

    void start();
    //    virtual void cancel() {}

    State state() const { return state_; }

protected:
    virtual void doStart() = 0;

protected slots:
    void finish();

signals:
    void progress(qreal);
    void finished();
    void stateChanged();

private:
    void setState(State state);

    State state_;
};

class ParallelBackgroundTask : public BackgroundTask
{
    Q_OBJECT
public:
    ParallelBackgroundTask(QObject* parent = 0);

    void addTask(BackgroundTask*);

protected:
    void doStart() override;

private:
    void taskFinished();

    QList<BackgroundTask*> tasks_;
    int executingTasks_;
};

}
