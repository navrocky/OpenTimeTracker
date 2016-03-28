#pragma once

#include <QSet>

#include "entitylist.h"
#include "common.h"
#include "../error.h"
#include "../errorcode.h"

namespace Core
{
namespace Model
{

template <class Entity>
class EntitySync
{
public:
    EntitySync(EntityList<Entity>& list, InternalId connectionId)
        : list_(list)
        , connectionId_(connectionId)
    {
        for (const auto& e : list.entities())
        {
            if (e->connectionId == connectionId)
                outdatedIds_.insert(e->externalId);
        }
    }

    std::shared_ptr<Entity> get(const QString& id) const
    {
        auto project = Entity::tryGetByExtId(list_.entities(), id, connectionId_);
        if (!project)
        {
            project = std::make_shared<Entity>();
            project->externalId = id;
            project->connectionId = connectionId_;
        }
        return project;
    }

    void release(const std::shared_ptr<Entity>& project)
    {
        if (project->isNew())
            list_.add(project);
        else
        {
            outdatedIds_.remove(project->externalId);
            if (!project->save())
                throw Error(Core::ErrorCode::Database, "<59090fe7> Cannot save entity");
        }
    }

    void removeOutdated()
    {
        auto entsCopy = list_.entities();
        for (const auto& e : entsCopy)
        {
            if (outdatedIds_.contains(e->externalId))
                list_.remove(e);
        }
    }

private:
    EntityList<Entity>& list_;
    InternalId connectionId_;
    QSet<QString> outdatedIds_;
};

}
}
