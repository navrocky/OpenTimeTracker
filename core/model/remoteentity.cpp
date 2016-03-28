#include "remoteentity.h"

#include <cassert>

namespace Core
{
namespace Model
{

RemoteEntity::RemoteEntity()
    : connectionId(0)
{
}

int RemoteEntity::internalId() const
{
    bool ok;
    int id = pk().toInt(&ok);
    assert(ok);
    return id;
}

bool RemoteEntity::isNew() const
{
    return pk().isNull();
}

}
}
