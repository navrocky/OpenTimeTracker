#pragma once

#include <memory>
#include <QList>
#include <3rdparty/qdjangodb/QDjangoQuerySet.h>

namespace Core
{
namespace Model
{

template <class Model>
QList<std::shared_ptr<Model>> querySetToList(const QDjangoQuerySet<Model>& set)
{
    QList<std::shared_ptr<Model>> res;
    QDjangoQuerySet<Model> setCopy = set;
    for (int i = 0, size = setCopy.size(); i < size; i++)
    {
        auto obj = std::make_shared<Model>();
        setCopy.at(i, obj.get());
        res << obj;
    }
    return res;
}

}
}
