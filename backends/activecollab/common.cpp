#include "common.h"

#include <QNetworkReply>
#include <QDomDocument>
#include <core/error.h>

using namespace Core;

namespace ActiveCollab
{

QDomDocument checkReplyAndParseXml(QNetworkReply *reply)
{
    checkReply(reply);

    QString errorMsg;
    int errorLine = 0;
    int errorColumn = 0;

    QDomDocument doc;
    if (!doc.setContent(reply, &errorMsg, &errorLine, &errorColumn))
        throw Error(Error::Network, QObject::tr("Error of parsing reply"),
                    QObject::tr("%1 line:%2 col:%3").arg(errorMsg).arg(errorLine).arg(errorColumn));

    qDebug() << "<8e4686ac>" << doc.toString();

    return doc;
}

void checkReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
        throw Error(Error::Network, reply->errorString());
}

}
