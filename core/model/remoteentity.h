#pragma once

#include <3rdparty/qdjangodb/QDjangoModel.h>

#include "common.h"

namespace Core
{
namespace Model
{

class RemoteEntity : public QDjangoModel
{

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(InternalId connectionId MEMBER connectionId)

public:
    RemoteEntity();

    QString id;
    InternalId connectionId;
};

}
}
