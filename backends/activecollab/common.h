#pragma once

class QDomDocument;
class QNetworkReply;

namespace ActiveCollab
{

void checkReply(QNetworkReply* reply);

QDomDocument checkReplyAndParseXml(QNetworkReply* reply);

}
