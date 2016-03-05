#pragma once

#include <vector>
#include <QString>
#include "errorcode.h"
#include "pointers.h"

namespace Core
{

class ErrorDescription
{
public:
    ErrorDescription(ErrorCode code, const QString& message, const QString& additional = QString(),
                     const std::vector<ErrorDescriptionPtr>& innerErrors = {});

    static ErrorDescriptionPtr create(ErrorCode code, const QString& message, const QString& additional = QString(),
                                      const std::vector<ErrorDescriptionPtr>& innerErrors = {});

    ErrorCode code() const { return code_; }
    QString message() const { return message_; }
    QString additional() const { return additional_; }
    const std::vector<ErrorDescriptionPtr>& innerErrors() const { return innerErrors_; }

    void addInnerError(const ErrorDescriptionPtr& error);

    QString codeStr() const;


private:
    ErrorCode code_;
    QString message_;
    QString additional_;
    std::vector<ErrorDescriptionPtr> innerErrors_;
};

}
