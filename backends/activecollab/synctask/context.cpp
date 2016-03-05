#include "context.h"

#include <QUrlQuery>

namespace ActiveCollab
{
namespace SyncTask
{

QUrl Context::getUrl(const QString& command) const
{
    QUrl url(apiUrl);
    QUrlQuery query;
    query.addQueryItem("path_info", command);
    query.addQueryItem("auth_api_token", token);
    url.setQuery(query);
    return url;
}

}
}
