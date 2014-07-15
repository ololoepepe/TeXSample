#include "tglobal.h"
#include "taccesslevel.h"
#include "tclientinfo.h"
#include "tidlist.h"
#include "tinviteinfo.h"
#include "tinviteinfolist.h"
#include "tlabinfo.h"
#include "tlabinfolist.h"
#include "tproject.h"
#include "tmessage.h"
#include "tbinaryfile.h"
#include "tbinaryfilelist.h"
#include "ttexfile.h"
#include "ttexfilelist.h"
#include "tsampleinfo.h"
#include "tsampleinfolist.h"
#include "tservice.h"
#include "tservicelist.h"
#include "ttexproject.h"
#include "tuserinfo.h"
#include "tnamespace.h"

#include <BeQtGlobal>

#include <QMetaType>

void tRegister()
{
    static bool registered = false;
    if (registered)
        return;
    bRegister();
    qRegisterMetaType<TAccessLevel>();
    qRegisterMetaTypeStreamOperators<TAccessLevel>();
    qRegisterMetaType<TClientInfo>();
    qRegisterMetaTypeStreamOperators<TClientInfo>();
    qRegisterMetaType<TBinaryFile>();
    qRegisterMetaTypeStreamOperators<TBinaryFile>();
    qRegisterMetaType<TBinaryFileList>();
    qRegisterMetaTypeStreamOperators<TBinaryFileList>();
    qRegisterMetaType<TTexFile>();
    qRegisterMetaTypeStreamOperators<TTexFile>();
    qRegisterMetaType<TTexFileList>();
    qRegisterMetaTypeStreamOperators<TTexFileList>();
    qRegisterMetaType<TIdList>();
    qRegisterMetaTypeStreamOperators<TIdList>();
    qRegisterMetaType<TInviteInfo>();
    qRegisterMetaTypeStreamOperators<TInviteInfo>();
    qRegisterMetaType<TInviteInfoList>();
    qRegisterMetaTypeStreamOperators<TInviteInfoList>();
    qRegisterMetaType<TLabInfo>();
    qRegisterMetaTypeStreamOperators<TLabInfo>();
    qRegisterMetaType<TLabInfoList>();
    qRegisterMetaTypeStreamOperators<TLabInfoList>();
    qRegisterMetaType<TProject>();
    qRegisterMetaTypeStreamOperators<TProject>();
    qRegisterMetaType<TMessage>();
    qRegisterMetaTypeStreamOperators<TMessage>();
    qRegisterMetaType<TSampleInfo>();
    qRegisterMetaTypeStreamOperators<TSampleInfo>();
    qRegisterMetaType<TSampleInfoList>();
    qRegisterMetaTypeStreamOperators<TSampleInfoList>();
    qRegisterMetaType<TService>();
    qRegisterMetaTypeStreamOperators<TService>();
    qRegisterMetaType<TServiceList>();
    qRegisterMetaTypeStreamOperators<TServiceList>();
    qRegisterMetaType<TTexProject>();
    qRegisterMetaTypeStreamOperators<TTexProject>();
    qRegisterMetaType<TUserInfo>();
    qRegisterMetaTypeStreamOperators<TUserInfo>();
    registered = true;
}

const char *tVersion()
{
    return "2.0.0-beta";
}
