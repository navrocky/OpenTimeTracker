#include "dbtools.h"

#include <QObject>
#include <QSqlError>

#include <core/error.h>

using namespace Core;

namespace DBTools
{

void execQueryAndCheck(const QString& query)
{
    QSqlQuery q;
    q.prepare(query);
    execQueryAndCheck(q);
}

void execQueryAndCheck(QSqlQuery& query)
{
    if (!query.exec())
        throw Error(Error::Database, QObject::tr("Error executing query"), query.lastError().text());
}

}
