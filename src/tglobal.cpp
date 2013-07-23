#include "tglobal.h"
#include "taccesslevel.h"
#include "tclientinfo.h"
#include "tcompilationresult.h"
#include "tcompiledproject.h"
#include "tcompilerparameters.h"
#include "tidlist.h"
#include "tinviteinfo.h"
#include "tinviteinfolist.h"
#include "tmessage.h"
#include "toperationresult.h"
#include "tproject.h"
#include "tprojectfile.h"
#include "tprojectfilelist.h"
#include "tsampleinfo.h"
#include "tsampleinfolist.h"
#include "tservice.h"
#include "tservicelist.h"
#include "tnamespace.h"
#include "tuserinfo.h"
#include "tprojectfilelist.h"

#include <BeQtGlobal>

#include <QMetaType>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QUuid>
Q_DECLARE_METATYPE(QUuid)
#endif

void tInit()
{
    static bool registered = false;
    if (registered)
        return;
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_INIT_RESOURCE(texsample);
    Q_INIT_RESOURCE(texsample_translations);
#endif
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    qRegisterMetaType<QUuid>();
    qRegisterMetaTypeStreamOperators<QUuid>();
#endif
    bRegister();
    qRegisterMetaType<TAccessLevel>();
    qRegisterMetaTypeStreamOperators<TAccessLevel>();
    qRegisterMetaType<TClientInfo>();
    qRegisterMetaTypeStreamOperators<TClientInfo>();
    qRegisterMetaType<TCompilationResult>();
    qRegisterMetaTypeStreamOperators<TCompilationResult>();
    qRegisterMetaType<TCompiledProject>();
    qRegisterMetaTypeStreamOperators<TCompiledProject>();
    qRegisterMetaType<TCompilerParameters>();
    qRegisterMetaTypeStreamOperators<TCompilerParameters>();
    qRegisterMetaType<TIdList>();
    qRegisterMetaTypeStreamOperators<TIdList>();
    qRegisterMetaType<TInviteInfo>();
    qRegisterMetaTypeStreamOperators<TInviteInfo>();
    qRegisterMetaType<TInviteInfoList>();
    qRegisterMetaTypeStreamOperators<TInviteInfoList>();
    qRegisterMetaType<TMessage>();
    qRegisterMetaTypeStreamOperators<TMessage>();
    qRegisterMetaType<TOperationResult>();
    qRegisterMetaTypeStreamOperators<TOperationResult>();
    qRegisterMetaType<TProject>();
    qRegisterMetaTypeStreamOperators<TProject>();
    qRegisterMetaType<TProjectFile>();
    qRegisterMetaTypeStreamOperators<TProjectFile>();
    qRegisterMetaType<TProjectFileList>();
    qRegisterMetaTypeStreamOperators<TProjectFileList>();
    qRegisterMetaType<TSampleInfo>();
    qRegisterMetaTypeStreamOperators<TSampleInfo>();
    qRegisterMetaType<TSampleInfoList>();
    qRegisterMetaTypeStreamOperators<TSampleInfoList>();
    qRegisterMetaType<TService>();
    qRegisterMetaTypeStreamOperators<TService>();
    qRegisterMetaType<TServiceList>();
    qRegisterMetaTypeStreamOperators<TServiceList>();
    qRegisterMetaType<TUserInfo>();
    qRegisterMetaTypeStreamOperators<TUserInfo>();
    registered = true;
}

void tCleanup()
{
#if defined(TSMP_BUILTIN_RESOURCES)
     Q_CLEANUP_RESOURCE(texsample);
     Q_CLEANUP_RESOURCE(texsample_translations);
#endif
}

const char *tVersion()
{
    return "1.0.0-a2";
}
