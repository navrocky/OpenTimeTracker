#include "modelregistration.h"

#include <3rdparty/qdjangodb/QDjango.h>

#include "info.h"
#include "connection.h"
#include "project.h"
#include "milestone.h"
#include "task.h"

namespace Core
{
namespace Model
{

void registerModels()
{
    QDjango::registerModel<Info>();
    QDjango::registerModel<Connection>();
    QDjango::registerModel<Project>();
    QDjango::registerModel<Milestone>();
    QDjango::registerModel<Task>();
}

}
}
