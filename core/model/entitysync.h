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
        for (const auto& e : list)
        {
            if (e->connectionId == connectionId)
                outdatedIds_.insert(e->externalId);
        }
    }

    std::shared_ptr<Entity> get(const QString& id) const
    {
        auto project = Entity::get(list_, id, connectionId_);
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
            list_.addEntity(project);
        else
        {
            outdatedIds_.remove(project->externalId);
            if (!project->save())
                throw Error(Core::ErrorCode::Database, "<59090fe7> Cannot save entity");
        }
    }

    void removeOutdated()
    {
        for (int i = 0; i < list_.size();)
        {
            const auto& e = list_[i];
            if (outdatedIds_.contains(e->externalId))
            {
                list_.removeAt(i);
                e->remove();
            }
            else
                i++;
        }
    }

private:
    EntityList<Entity>& list_;
    InternalId connectionId_;
    QSet<QString> outdatedIds_;
};

}
}
