#pragma once

#include <memory>

class Context;
typedef std::shared_ptr<Context> ContextPtr;

namespace Core
{
namespace PMS
{
class BackendPlugin;
}
}
typedef std::shared_ptr<Core::PMS::BackendPlugin> BackendPluginPtr;
