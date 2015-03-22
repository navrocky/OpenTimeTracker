#include "connection.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QPointer>
#include <QVariant>
#include <QDomDocument>
#include <QApplication>

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
    updateValidFlag();
}

void Connection::setUserEmail(const QString &v)
{
    if (userEmail_ == v)
        return;
    userEmail_ = v;
    emit connectionChanged();
}

void Connection::setApiKey(const QString &v)
{
    if (apiKey_ == v)
        return;
    apiKey_ = v;
    emit connectionChanged();
    updateValidFlag();
}

void Connection::load(const QVariantMap& m)
{
    setTitle(m["title"].toString());
    setApiUrl(m["apiUrl"].toString());
    setUserEmail(m["userEmail"].toString());
    setApiKey(m["apiKey"].toString());
}

void Connection::save(QVariantMap& m) const
{
    m["title"] = title();
    m["apiUrl"] = apiUrl();
    m["userEmail"] = userEmail();
    m["apiKey"] = apiKey();
}

QNetworkReply* Connection::checkConnection(Core::PMS::SimpleResultHandler handler)
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
            auto elem = doc.documentElement();
            if (elem.isNull() || elem.tagName() != "api_is_alive")
                throw Error(Error::Parse);

            handler(Error());
        }
        catch (const Error& err)
        {
            handler(err);
        }
    });
}

QNetworkReply* Connection::connectToAccount(const QString &email,
                                            const QString &password,
                                            PMS::SimpleResultHandler handler)
{
    QUrlQuery query;
    query.addQueryItem("api_subscription[email]", email);
    query.addQueryItem("api_subscription[password]", password);
    query.addQueryItem("api_subscription[client_name]", qApp->applicationName());
    query.addQueryItem("api_subscription[client_vendor]", qApp->organizationName());
    QNetworkRequest request(apiUrl_);
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/x-www-form-urlencoded");
    auto reply = client_->post(request, query.toString().toUtf8());

    QPointer<QObject> self = this;
    QObject::connect(reply, &QNetworkReply::finished, [self, this, reply, handler]()
    {
        if (!self)
            return;
        try
        {
            checkReply(reply);
            auto str = reply->readAll().trimmed();

            QRegExp apiKeyRx("^API key: (.+)$");
            if (apiKeyRx.exactMatch(str))
            {
                setApiKey(apiKeyRx.cap(1));
                handler(Error());
                return;
            }

            QRegExp errorRx("^Error Code: (\\d+)$");
            if (errorRx.exactMatch(str))
            {
                int code = errorRx.cap(1).toInt();
                QString error;
                switch (code)
                {
                    case 1: error = tr("Client details not set"); break;
                    case 2: error = tr("Unknown user"); break;
                    case 3: error = tr("Invalid password"); break;
                    case 4: error = tr("Not allowed for given User and their System Role"); break;
                    default: error = tr("Unknown error"); break;
                }
                throw Error(Error::Authorization, error);
            }

            throw Error(Error::Authorization, tr("Unknown error"));
        }
        catch (const Error& err)
        {
            handler(err);
        }
    });
}

void Connection::updateValidFlag()
{
    setValid(!apiUrl().isEmpty() && !apiKey().isEmpty());
}

}
