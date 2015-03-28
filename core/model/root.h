#pragma once

#include <QList>

#include "pointers.h"

namespace Core
{
namespace Model
{

class Root
{
public:
    void init();

    void addProject(ProjectPtr project);
//    void removeProject(ProjectPtr project);

    QList<ProjectPtr> projects() const { return projects_; }

private:
    QList<ProjectPtr> projects_;
};

}
}
