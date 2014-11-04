#pragma once

#include <memory>

class Application;
typedef std::shared_ptr<Application> ContextPtr;

namespace Core
{
namespace PMS
{
class BackendPlugin;
class Connection;
}
}
typedef std::shared_ptr<Core::PMS::BackendPlugin> BackendPluginPtr;
typedef std::shared_ptr<Core::PMS::Connection> ConnectionPtr;
