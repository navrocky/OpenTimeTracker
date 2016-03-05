#pragma once

#include <exception>
#include <QString>
#include "implicitsharing.h"
#include "errorcode.h"
#include "pointers.h"

namespace Core
{

class Error : public std::exception
{
public:
    Error();
    Error(const ErrorDescriptionPtr& descr);
    Error(ErrorCode code);
    Error(ErrorCode code, const QString& message, const QString& additional = QString());
    Error(const QString& message, const QString& additional = QString());

    ErrorCode code() const;
    QString message() const;
    QString codeStr() const;

    bool hasError() const;

    const char* what() const throw();

    ErrorDescriptionPtr description() const;

private:
    void updateWhatMessage();


    struct Data;
    ImplicitSharing<Data> d;
};

#define CATCH_ERROR(LogName) \
    catch (const std::exception& e) \
    { \
        qCCritical(LogName) << e.what(); \
    }

}
