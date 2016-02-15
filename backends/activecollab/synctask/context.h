#pragma once

#include <core/model/pointers.h>

class QNetworkAccessManager;

namespace ActiveCollab
{
namespace SyncTask
{

class Context
{
public:
    QNetworkAccessManager* client;
    Core::Model::RootPtr root;
};

}
}
