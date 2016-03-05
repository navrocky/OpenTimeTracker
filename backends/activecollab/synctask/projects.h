#pragma once

#include <QObject>
#include <core/backgroundtask.h>
#include "pointers.h"

namespace ActiveCollab
{
namespace SyncTask
{

class Projects : public Core::BackgroundTask
{
    Q_OBJECT
public:
    Projects(const ContextPtr& ctx, QObject* parent = 0);

protected:
    void doStart() override;

private:
    void replyFinished();

    ContextPtr ctx_;
};

}
}
