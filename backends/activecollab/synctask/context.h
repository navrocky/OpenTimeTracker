#pragma once

#include <QString>
#include <QUrl>
#include <core/model/pointers.h>
#include <core/model/common.h>

class QNetworkAccessManager;

namespace ActiveCollab
{
namespace SyncTask
{

class Context
{
public:
    Context();

    QString apiUrl;
    QString token;
    QNetworkAccessManager* client;
    Core::Model::RootPtr root;
    Core::Model::InternalId connectionId;

    QUrl getUrl(const QString& command) const;
};

}
}
