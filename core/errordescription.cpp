#include "errordescription.h"

#include <QObject>

namespace Core
{

ErrorDescription::ErrorDescription(ErrorCode code, const QString& message, const QString& additional,
                                   const std::vector<ErrorDescriptionPtr>& innerErrors)
    : code_(code)
    , message_(message)
    , additional_(additional)
    , innerErrors_(innerErrors)
{
}

ErrorDescriptionPtr ErrorDescription::create(ErrorCode code, const QString& message, const QString& additional,
        const std::vector<ErrorDescriptionPtr>& innerErrors)
{
    return std::make_shared<ErrorDescription>(code, message, additional, innerErrors);
}

void ErrorDescription::addInnerError(const ErrorDescriptionPtr& error)
{
    innerErrors_.push_back(error);
}

QString ErrorDescription::codeStr() const
{
    switch (code_)
    {
        case ErrorCode::NoError:
            return QObject::tr("No error");
        case ErrorCode::Unclassified:
            return QObject::tr("Unclassified error");
        case ErrorCode::Network:
            return QObject::tr("Network error");
    }
    return QString();
}

}
