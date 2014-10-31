#pragma once

#include <QObject>

namespace Core
{

class PMSBackend : public QObject
{
    Q_OBJECT
public:
    PMSBackend(QObject* parent = 0);

    virtual QWidget* createOptionsWidget(QWidget* parent) = 0;
};

}
