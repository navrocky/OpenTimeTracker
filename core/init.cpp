#include "init.h"

#include <QMetaType>

#include "errordescription.h"

Q_DECLARE_METATYPE(Core::ErrorDescriptionPtr)

namespace Core
{

void init()
{
    qRegisterMetaType<ErrorDescriptionPtr>();
}

}
