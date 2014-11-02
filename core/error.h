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
        NoError,
        Unclassified,
        Network,
        Parse
    };

    Error();
    Error(Code code);
    Error(Code code, const QString& message, const QString& additional = QString());
    Error(const QString& message, const QString& additional = QString());

    Code code() const;
    QString message() const;
    QString codeStr() const;

    bool hasError() const;

private:
    struct Data;
    ImplicitSharing<Data> d;
};

}
