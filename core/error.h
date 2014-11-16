#pragma once

#include <exception>
#include <QString>
#include "implicitsharing.h"

namespace Core
{

class Error : public std::exception
{
public:
    enum Code
    {
        NoError = 0,
        Unclassified = 1,
        Network = 2,
        Parse = 3,
        Database = 4
    };

    Error();
    Error(Code code);
    Error(Code code, const QString& message, const QString& additional = QString());
    Error(const QString& message, const QString& additional = QString());

    Code code() const;
    QString message() const;
    QString codeStr() const;

    bool hasError() const;

    const char* what() const throw();

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
