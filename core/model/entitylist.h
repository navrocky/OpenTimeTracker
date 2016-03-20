#pragma once

#include <memory>
#include <QList>
#include <3rdparty/qdjangodb/QDjangoQuerySet.h>
#include "tools.h"

namespace Core
{
namespace Model
{

template <typename T>
class EntityList : public QList<std::shared_ptr<T>>
{
public:
    typedef typename std::shared_ptr<T> EntityPtr;

    void init()
    {
        querySetToList(QDjangoQuerySet<T>().all(), *this);
    }

    void addEntity(const EntityPtr& e)
    {
        if (!e->pk().isNull())
            throw std::runtime_error("<c4277f49> Entity already added");
        if (!e->save())
            throw std::runtime_error("<03ebdefd> Cannot save entity");
        this->append(e);
    }
};

}
}
