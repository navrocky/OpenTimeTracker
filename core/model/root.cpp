#include "root.h"

#include <stdexcept>
#include <QVariant>

#include <3rdparty/qdjangodb/QDjangoQuerySet.h>

#include "tools.h"
#include "project.h"

namespace Core
{
namespace Model
{

void Root::init()
{
    projects.init();
}

//void Root::addProject(ProjectPtr project)
//{
//    if (!project->pk().isNull())
//        throw std::runtime_error("<c4277f49> Project already added");
//    project->save();
//    projects_ << project;
//}

//void Root::removeProject(ProjectPtr project)
//{

//}

}
}
