#include "backend.h"

namespace ActiveCollab
{

Backend::Backend(QObject *parent)
    : Core::PMSBackend(parent)
{
}

QWidget *Backend::createOptionsWidget(QWidget *parent)
{
    return 0;
}

}
