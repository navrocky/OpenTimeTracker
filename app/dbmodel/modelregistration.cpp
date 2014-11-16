#include "modelregistration.h"

#include <3rdparty/qdjangodb/QDjango.h>

#include "info.h"
#include "connection.h"

namespace DBModel
{

void registerModels()
{
    QDjango::registerModel<Info>();
    QDjango::registerModel<Connection>();
}

}
