#pragma once

#include <QObject>
#include <core/backgroundtask.h>
#include <core/model/pointers.h>
#include "pointers.h"

class QXmlStreamReader;

namespace ActiveCollab
{
namespace SyncTask
{

class Projects : public Core::BackgroundTask
{
    Q_OBJECT
public:
    Projects(const ContextPtr& ctx, QObject* parent = 0);

protected:
    void doStart() override;

private:
    void replyFinished();
    void parseProject(QXmlStreamReader* xml, QList<Core::Model::ProjectPtr>& projects);

    ContextPtr ctx_;
};

}
}
