#pragma once

#include <QUrl>
#include <QNetworkAccessManager>

#include <core/pmsbackend.h>

namespace ActiveCollab
{

class Connection : public Core::PMS::Connection
{
    Q_OBJECT
public:
    Connection(const Core::PMS::BackendPlugin* plugin, QObject* parent = 0);

    QString apiUrl() const { return apiUrl_; }
    void setApiUrl(const QString& v);

    QString userEmail() const { return userEmail_; }
    void setUserEmail(const QString& v);

    QString apiKey() const { return apiKey_; }
    void setApiKey(const QString& v);

    void load(const QVariantMap&) override;
    void save(QVariantMap&) const override;

    QNetworkReply* checkConnection(Core::PMS::SimpleResultHandler);

    QNetworkReply* connectToAccount(const QString& email, const QString& password, Core::PMS::SimpleResultHandler handler);

private:
    QString apiUrl_;
    QString userEmail_;
    QString apiKey_;
    QNetworkAccessManager* client_;
};

}
