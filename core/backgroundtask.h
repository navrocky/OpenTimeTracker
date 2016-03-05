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
    void startDetached(BackgroundTask* task, bool showError = false);

    bool isBusy() const { return busy_; }

signals:
    void busyChanged(bool);
    void showTaskError(Core::ErrorDescriptionPtr);

private slots:
    void taskStateChanged();
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

    enum Option
    {
        ShowError = 1 << 0
    };
    Q_DECLARE_FLAGS(Options, Option)

    BackgroundTask(const QString& title = QString(), QObject* parent = 0);

    void start();

    Options options() const { return opts_; }
    void setOptions(Options v) { opts_ = v; }

    QString title() const { return title_; }
    State state() const { return state_; }
    ErrorDescriptionPtr error() const { return errorDescription_; }

protected:
    virtual void doStart() = 0;
    void setError(const ErrorDescriptionPtr& error);

protected slots:
    void finish();

signals:
    void progress(qreal);
    void finished();
    void stateChanged();

private:
    void setState(State state);

    QString title_;
    State state_;
    ErrorDescriptionPtr errorDescription_;
    Options opts_;
};

class ParallelBackgroundTask : public BackgroundTask
{
    Q_OBJECT
public:
    ParallelBackgroundTask(const QString& title, QObject* parent = 0);

    void addTask(BackgroundTask*);

protected:
    void doStart() override;

private:
    void taskFinished();

    QList<BackgroundTask*> tasks_;
    int executingTasks_;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(Core::BackgroundTask::Options)
