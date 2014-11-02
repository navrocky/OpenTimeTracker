#pragma once

class QDomDocument;
class QNetworkReply;

namespace ActiveCollab
{

QDomDocument checkReplyAndParseXml(QNetworkReply* reply);

}
