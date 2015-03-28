#pragma once

#include <memory>

#define DECL_POINTER(ClassName) \
    class ClassName; \
    typedef std::shared_ptr<ClassName> ClassName##Ptr; \
    typedef std::weak_ptr<ClassName> ClassName##WeakPtr;

namespace Core
{
namespace Model
{

DECL_POINTER(Root)
DECL_POINTER(Project)

}
}
