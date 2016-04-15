#include "project.h"

#include <3rdparty/qdjangodb/QDjangoQuerySet.h>
#include <3rdparty/qdjangodb/QDjangoWhere.h>
#include "tools.h"

namespace Core
{
namespace Model
{

Project::Project()
{
}

TaskList& Project::tasks()
{
    if (!tasks_)
        tasks_ = TaskList(internalId());
    return *tasks_;
}

TaskList::TaskList(int projectId)
    : projectId_(projectId)
{
}

TaskList::QuerySet TaskList::querySet() const
{
    return QuerySet().filter(QDjangoWhere("projectId", QDjangoWhere::Equals, projectId_));
}

void TaskList::add(const EntityPtr& e)
{
    e->projectId = projectId_;
    EntityList<Task>::add(e);
}

}
}
