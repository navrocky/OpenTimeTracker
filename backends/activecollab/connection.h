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
    void setApiUrl(const QString& v) { apiUrl_ = v; }

    void load(const QVariantMap&) override;
    void save(QVariantMap&) const override;

    void checkConnection(Core::PMS::SimpleResultHandler);

private:
    QString apiUrl_;
    QNetworkAccessManager* client_;
};

}
