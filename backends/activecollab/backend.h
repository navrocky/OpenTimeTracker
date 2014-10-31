#pragma once

#include <QObject>
#include <core/pmsbackend.h>

namespace ActiveCollab
{

class Backend : public Core::PMSBackend
{
    Q_OBJECT
public:
    Backend(QObject* parent = 0);

    QWidget* createOptionsWidget(QWidget* parent) override;
};

}
