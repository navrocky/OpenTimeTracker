#include "connection.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QPointer>
#include <QVariant>
#include <QDomDocument>

#include "common.h"

using namespace Core;

namespace ActiveCollab
{

Connection::Connection(const PMS::BackendPlugin *plugin, QObject* parent)
    : Core::PMS::Connection(plugin, parent)
    , client_(new QNetworkAccessManager(this))
{
}

void Connection::setApiUrl(const QString &v)
{
    if (apiUrl_ == v)
        return;
    apiUrl_ = v;
    emit connectionChanged();
}

void Connection::load(const QVariantMap& m)
{
    setTitle(m["title"].toString());
    setApiUrl(m["apiUrl"].toString());
}

void Connection::save(QVariantMap& m) const
{
    m["title"] = title();
    m["apiUrl"] = apiUrl();
}

void Connection::checkConnection(Core::PMS::SimpleResultHandler handler)
{
    QUrl url(apiUrl_);
    QUrlQuery query;
    query.addQueryItem("check_if_alive", "1");
    url.setQuery(query);
    auto reply = client_->get(QNetworkRequest(url));

    QPointer<QObject> self = this;
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, handler]()
    {
        if (!self)
            return;

        try
        {
            auto doc = checkReplyAndParseXml(reply);
            auto elem = doc.documentElement().firstChildElement("api_is_alive");
            if (elem.isNull())
                throw Error(Error::Parse);

            handler(Error());
        }
        catch (const Error& err)
        {
            handler(err);
        }
    });
}

}
