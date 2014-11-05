#include "error.h"

#include <QByteArray>
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
    QByteArray whatMessage;
};

Error::Error()
{
}

Error::Error(Error::Code code)
{
    d->code = code;
}

Error::Error(Error::Code code, const QString& message, const QString& additional)
{
    d->code = code;
    d->message = message;
    d->additional = additional;
    updateWhatMessage();
}

Error::Error(const QString& message, const QString& additional)
{
    d->code = Unclassified;
    d->message = message;
    d->additional = additional;
    updateWhatMessage();
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
        case NoError:
            return QObject::tr("No error");
        case Unclassified:
            return QObject::tr("Unclassified error");
        case Network:
            return QObject::tr("Network error");
    }
    return QString();
}

bool Error::hasError() const
{
    return d->code != NoError;
}

const char* Error::what() const throw()
{
    return d->whatMessage.data();
}

void Error::updateWhatMessage()
{
    QString additional = !d->additional.isEmpty() ? QString(" [%1]").arg(d->additional) : QString();
    d->whatMessage = QString("(%1) %2%3").arg(d->code).arg(d->message).arg(additional).toUtf8();
}

}
