#pragma once

#include <3rdparty/qdjangodb/QDjangoModel.h>

#include "common.h"

namespace Core
{
namespace Model
{

class Assignee : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER name)
public:
    QString name;
};

class UserGroup : public Assignee
{
    Q_OBJECT
    Q_PROPERTY(InternalId parentId MEMBER parentId)
public:
    InternalId parentId;
};

class User : public Assignee
{
    Q_OBJECT
    Q_PROPERTY(InternalId groupId MEMBER groupId)
public:
    InternalId groupId;
};

}
}
