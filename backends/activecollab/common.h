#pragma once

#include <QString>
#include <core/error.h>

class QDomDocument;
class QNetworkReply;
class QXmlStreamReader;

namespace ActiveCollab
{

void checkReply(QNetworkReply* reply);

QDomDocument checkReplyAndParseXml(QNetworkReply* reply);

void throwXmlError(QXmlStreamReader* xml, const QString& description);

#define CATCH_ERROR_IN_TASK \
    catch (const Core::Error& e) { setError(e.description()); } \
    catch (const std::exception& e) { setError(Core::ErrorDescription::create(Core::ErrorCode::Unclassified, QString::fromUtf8(e.what()))); }

}
