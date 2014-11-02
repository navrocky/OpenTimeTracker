#include "error.h"

#include <QObject>

namespace Core
{

struct Error::Data
{
    Data()
        : code(Error::NoError)
    {}

    Error::Code code;
    QString message;
    QString additional;
};

Error::Error()
{
}

Error::Error(Error::Code code)
{
    d->code = code;
}

Error::Error(Error::Code code, const QString &message, const QString &additional)
{
    d->code = code;
    d->message = message;
    d->additional = additional;
}

Error::Error(const QString &message, const QString &additional)
{
    d->code = Unclassified;
    d->message = message;
    d->additional = additional;
}

Error::Code Error::code() const
{
    return d->code;
}

QString Error::message() const
{
    return d->message;
}

QString Error::codeStr() const
{
    switch (d->code)
    {
        case NoError: return QObject::tr("No error");
        case Unclassified: return QObject::tr("Unclassified error");
        case Network: return QObject::tr("Network error");
    }
    return QString();
}

bool Error::hasError() const
{
    return d->code != NoError;
}

}
