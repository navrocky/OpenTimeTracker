#include "backend.h"

namespace Core
{
namespace PMS
{

BackendPlugin::BackendPlugin(const ApplicationContextPtr& ctx, QObject* parent)
    : QObject(parent)
    , ctx_(ctx)
{
}

}
}
