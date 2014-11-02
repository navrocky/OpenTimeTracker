#pragma once

#include <memory>
#include <core/pmsbackend.h>
#include "pointers.h"

typedef QList<BackendPluginPtr> BackendPlugins;

class Context
{
public:
    BackendPlugins backends() const { return backends_; }

    template <typename T>
    void registerBackend()
    {
        backends_ << std::make_shared<T>();
    }

private:
    BackendPlugins backends_;
};
