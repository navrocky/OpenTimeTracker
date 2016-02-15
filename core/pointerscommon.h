#pragma once

#include <memory>

#define DECL_POINTER(ClassName) \
    class ClassName; \
    typedef std::shared_ptr<ClassName> ClassName##Ptr; \
    typedef std::weak_ptr<ClassName> ClassName##WeakPtr;
