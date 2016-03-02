#include "projects.h"

#include <QTimer>

namespace ActiveCollab
{
namespace SyncTask
{

Projects::Projects(const ContextPtr& ctx, QObject* parent)
    : Core::BackgroundTask(parent)
    , ctx_(ctx)
{


}

void Projects::doStart()
{
    QTimer::singleShot(1000, this, SLOT(finish()));
}

}
}
