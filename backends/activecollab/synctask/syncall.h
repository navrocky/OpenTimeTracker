#pragma once

#include <core/backgroundtask.h>
#include <core/model/pointers.h>
#include "pointers.h"

namespace ActiveCollab
{
namespace SyncTask
{

class SyncAll: public Core::BackgroundTask
{
    Q_OBJECT
public:
    SyncAll(const ContextPtr& ctx, QObject* parent = 0);

protected:
    void doStart() override;

private:
    ContextPtr ctx_;
};

}
}
