#pragma once

#include "model/pointers.h"

namespace Core
{

class TaskManager;

class ApplicationContext
{
public:
    ApplicationContext();

    Model::RootPtr rootModel;
    TaskManager* taskManager;
};

}
