#include "tglobal.h"
#include "tsampleinfo.h"

#include <QMetaType>

void tRegister()
{
    static bool registered = false;
    if (registered)
        return;
    qRegisterMetaType<TSampleInfo>();
    qRegisterMetaTypeStreamOperators<TSampleInfo>();
    registered = true;
}

const char *tVersion()
{
    return "1.0.0-pa";
}
