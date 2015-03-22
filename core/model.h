#pragma once

#include <QString>
#include <QList>
#include "implicitsharing.h"

namespace Core
{
namespace Model
{

class Project;

/// Root of all data
class Root
{
public:
    typedef QList<Project> Projects;



};

class Project
{
public:
    QString id() const;
    void setId(const QString&);

    QString name() const;
    void setName(const QString&);

    QString overview() const;
    void setOverview(const QString&);

private:
    struct Data;
    ImplicitSharing<Data> d;
};

class Milestone
{
};

class Task
{
};

}
}
