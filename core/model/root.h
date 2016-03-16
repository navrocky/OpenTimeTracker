#pragma once

#include <QList>

#include "pointers.h"
#include "entitylist.h"
#include "project.h"

namespace Core
{
namespace Model
{

class Root
{
public:
    void init();

//    void addProject(ProjectPtr project);
//    void removeProject(ProjectPtr project);

//    QList<ProjectPtr> projects() const { return projects_; }

    EntityList<Project> projects;

private:
};

}
}
