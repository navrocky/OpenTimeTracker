#pragma once

#include "pointers.h"
#include "remoteentity.h"
#include "entitylist.h"
#include "task.h"
#include "../optional.h"

namespace Core
{
namespace Model
{

class TaskList : public EntityList<Task>
{
public:
    TaskList(int projectId = 0);

    QuerySet querySet() const override;
    void add(const EntityPtr& e) override;

private:
    int projectId_;
};

class Project : public RemoteEntity
{
    Q_OBJECT
    Q_CLASSINFO("__meta__", "db_table=project")

    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString description MEMBER description)

public:
    Project();

    QString title;
    QString description;

    TaskList& tasks();

private:
    Optional<TaskList> tasks_;
};

}
}
