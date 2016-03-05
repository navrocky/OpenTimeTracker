#include "finalizator.h"

#include <exception>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(FINALIZATOR, "Finalizator")

Finalizator::~Finalizator()
{
    if (!canceled_ && func_)
    {
        try
        {
            func_();
        }
        catch (const std::exception& e)
        {
            qCCritical(FINALIZATOR) << e.what();
        }
        catch (...)
        {
            qCCritical(FINALIZATOR) << "Unknown error";
        }
    }
}

Finalizator::Finalizator(const Finalizator& src)
    : func_(src.func_)
    , canceled_(false)
{
    src.canceled_ = true;
}

void Finalizator::operator=(const Finalizator& src)
{
    func_ = src.func_;
    canceled_ = false;
    src.canceled_ = true;
}
