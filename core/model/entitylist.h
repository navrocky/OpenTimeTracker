#pragma once

#include <memory>
#include <QList>
#include <3rdparty/qdjangodb/QDjangoQuerySet.h>
#include "tools.h"
#include "../optional.h"

namespace Core
{
namespace Model
{

template <typename T>
class EntityList
{
public:
    typedef typename std::shared_ptr<T> EntityPtr;
    typedef QList<EntityPtr> Entities;
    typedef QDjangoQuerySet<T> QuerySet;

    virtual ~EntityList() {}

    virtual QuerySet querySet() const
    {
        return QuerySet().all();
    }

    const Entities& entities()
    {
        if (!entities_)
        {
            Entities ents;
            querySetToList(QDjangoQuerySet<T>().all(), ents);
            entities_ = ents;
        }
        return *entities_;
    }

    virtual void add(const EntityPtr& e)
    {
        if (!e->pk().isNull())
            throw std::runtime_error("<c4277f49> Entity already added");
        if (!e->save())
            throw std::runtime_error("<03ebdefd> Cannot save entity");
        (*entities_).append(e);
    }

    virtual void remove(const EntityPtr& e)
    {
        if (entities_)
        {
            (*entities_).removeAll(e);
        }
        e->remove();
    }

private:
    Optional<Entities> entities_;
};

}
}
