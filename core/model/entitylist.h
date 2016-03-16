#pragma once

#include <memory>
#include <QList>
#include <3rdparty/qdjangodb/QDjangoQuerySet.h>
#include "tools.h"

template <typename T>
class EntityList : public QList<std::shared_ptr<T>>
{
public:
    typedef typename std::shared_ptr<T> EntityPtr;

    void init()
    {
        querySetToList(QDjangoQuerySet<T>().all());
    }

    void addEntity(const EntityPtr& e)
    {
        if (!e->pk().isNull())
            throw std::runtime_error("<c4277f49> Entity already added");
        e->save();
        append(e);
    }

    int findById(const QString& id) const
    {
        for (int i = 0; i < this->size(); i++)
        {
            if (this->at(i)->id == id)
                return i;

        }
        return -1;
    }

    std::shared_ptr<T> getById(const QString& id) const
    {
        int i = findById(id);
        if (i >= 0)
            return this->at(i);
        else
            return nullptr;
    }

};
