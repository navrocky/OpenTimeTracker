#pragma once

#include <3rdparty/qdjangodb/QDjangoModel.h>

#include "common.h"

namespace Core
{
namespace Model
{

class RemoteEntity : public QDjangoModel
{
    Q_OBJECT

    Q_CLASSINFO("externalId", "db_column=external_id")
    Q_PROPERTY(QString externalId MEMBER externalId)

    Q_CLASSINFO("connectionId", "db_column=connection")
    Q_PROPERTY(int connectionId MEMBER connectionId)

public:
    RemoteEntity();

    QString externalId;
    int connectionId;

    bool isNew() const;

    template <class T>
    static int find(const T& list, const QString& id, InternalId connectionId)
    {
        for (int i = 0; i < list.size(); i++)
        {
            const auto& ent = list[i];
            if (ent->externalId == id && ent->connectionId == connectionId)
                return i;
        }
        return -1;
    }

    template <class T>
    static auto get(const T& list, const QString& id, InternalId connectionId) -> typename T::value_type
    {
        int i = find(list, id, connectionId);
        if (i >= 0)
            return list[i];
        else
            return typename T::value_type();
    }

};

}
}
