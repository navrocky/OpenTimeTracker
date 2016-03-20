#include "remoteentity.h"

namespace Core
{
namespace Model
{

RemoteEntity::RemoteEntity()
    : connectionId(0)
{
}

bool RemoteEntity::isNew() const
{
    return pk().isNull();
}

}
}
