#pragma once

#include <QSqlQuery>

namespace DBTools
{

void execQueryAndCheck(const QString& query);
void execQueryAndCheck(QSqlQuery& query);

}
