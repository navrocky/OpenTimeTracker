#pragma once

#include <QObject>
#include "pointers.h"

namespace ActiveCollab
{
namespace SyncTask
{

class Projects : public QObject
{
    Q_OBJECT
public:
    Projects(const ContextPtr& ctx);

    void exec();

private:
    ContextPtr ctx_;
};

}
}
