#include "model.h"

#include <QSharedData>
#include <QString>

namespace Core
{
namespace Model
{

struct Project::Data
{
    QString id;
    QString name;
    QString overview;
};

void Project::setId(const QString &v)
{
    d->id = v;
}

QString Project::name() const
{
    return d->name;
}

void Project::setName(const QString &v)
{
    d->name = v;
}

QString Project::overview() const
{
    return d->overview;
}

void Project::setOverview(const QString &v)
{
    d->overview = v;
}

}
}
