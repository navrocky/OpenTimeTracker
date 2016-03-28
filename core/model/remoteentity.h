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

    int internalId() const;

    QString externalId;
    int connectionId;

    bool isNew() const;

    template <class T>
    static int findByExtId(const T& list, const QString& externalId, InternalId connectionId)
    {
        for (int i = 0; i < list.size(); i++)
        {
            const auto& ent = list[i];
            if (ent->externalId == externalId && ent->connectionId == connectionId)
                return i;
        }
        return -1;
    }

    template <class T>
    static auto tryGetByExtId(const T& list, const QString& externalId, InternalId connectionId) -> typename T::value_type
    {
        int i = findByExtId(list, externalId, connectionId);
        if (i >= 0)
            return list[i];
        else
            return typename T::value_type();
    }

//    template <class T>
//    static int findByExtId(const T& list, const QString& externalId, InternalId connectionId)
//    {
//        for (int i = 0; i < list.size(); i++)
//        {
//            const auto& ent = list[i];
//            if (ent->externalId == externalId && ent->connectionId == connectionId)
//                return i;
//        }
//        return -1;
//    }



};

}
}
