#include "common.h"

#include <QNetworkReply>
#include <QDomDocument>
#include <QFile>
#include <QXmlStreamReader>
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
        throw Error(ErrorCode::Network, QObject::tr("Error of parsing reply"),
                    QObject::tr("%1 line:%2 col:%3").arg(errorMsg).arg(errorLine).arg(errorColumn));

    qDebug() << "<8e4686ac>" << doc.toString();

#if 0
    QFile f("result.xml");
    f.open(QFile::WriteOnly);
    f.write(doc.toString().toLocal8Bit());
#endif

    return doc;
}

void checkReply(QNetworkReply *reply)
{
    auto errorCode = reply->error();
    switch (errorCode)
    {
        case QNetworkReply::NoError:
            return;
        case QNetworkReply::ContentOperationNotPermittedError:
            throw Error(ErrorCode::Authorization, reply->errorString());
        default:
            throw Error(ErrorCode::Network, reply->errorString());
    }
}

void throwXmlError(QXmlStreamReader* xml, const QString& description)
{
    throw Error(ErrorCode::Parse, QObject::tr("%1\nLine %2, column %3")
                .arg(description)
                .arg(xml->lineNumber())
                .arg(xml->columnNumber()));
}

}
