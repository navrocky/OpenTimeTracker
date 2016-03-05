#include "error.h"

#include <QByteArray>
#include <QObject>

#include "errordescription.h"

namespace Core
{

struct Error::Data
{
    ErrorDescriptionPtr descr;
    QByteArray whatMessage;
};

Error::Error()
{
}

Error::Error(const ErrorDescriptionPtr& descr)
{
    d->descr = descr;
    updateWhatMessage();
}

Error::Error(ErrorCode code)
{
    d->descr = ErrorDescription::create(code, QString());
    updateWhatMessage();
}

Error::Error(ErrorCode code, const QString& message, const QString& additional)
{
    d->descr = ErrorDescription::create(code, message, additional);
    updateWhatMessage();
}

Error::Error(const QString& message, const QString& additional)
{
    d->descr = ErrorDescription::create(ErrorCode::Unclassified, message, additional);
    updateWhatMessage();
}

ErrorCode Error::code() const
{
    return d->descr->code();
}

QString Error::message() const
{
    return d->descr->message();
}

QString Error::codeStr() const
{
    return d->descr->codeStr();
}

bool Error::hasError() const
{
    return d->descr && d->descr->code() != ErrorCode::NoError;
}

const char* Error::what() const throw()
{
    return d->whatMessage.data();
}

ErrorDescriptionPtr Error::description() const
{
    return d->descr;
}

void Error::updateWhatMessage()
{
    QString additional = !d->descr->additional().isEmpty() ? QString(" [%1]").arg(d->descr->additional()) : QString();
    d->whatMessage = QString("(%1) %2%3").arg(static_cast<int>(d->descr->code())).arg(d->descr->message()).arg(
                         additional).toUtf8();
}

}
