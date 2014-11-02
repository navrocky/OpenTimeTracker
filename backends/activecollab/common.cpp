#include "common.h"

#include <QNetworkReply>
#include <QDomDocument>
#include <core/error.h>

using namespace Core;

namespace ActiveCollab
{

QDomDocument checkReplyAndParseXml(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
        throw Error(Error::Network, QObject::tr("Request error"), reply->errorString());

    QString errorMsg;
    int errorLine = 0;
    int errorColumn = 0;

    QDomDocument doc;
    if (!doc.setContent(reply, &errorMsg, &errorLine, &errorColumn))
        throw Error(Error::Network, QObject::tr("Error of parsing reply"),
                    QObject::tr("%1 line:%2 col:%3").arg(errorMsg).arg(errorLine).arg(errorColumn));

    return doc;
}

}
