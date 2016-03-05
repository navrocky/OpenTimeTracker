#pragma once

#include <QString>
#include <QUrl>
#include <core/model/pointers.h>

class QNetworkAccessManager;

namespace ActiveCollab
{
namespace SyncTask
{

class Context
{
public:
    QString apiUrl;
    QString token;
    QNetworkAccessManager* client;
    Core::Model::RootPtr root;

    QUrl getUrl(const QString& command) const;
};

}
}
