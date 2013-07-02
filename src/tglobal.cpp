#include "tglobal.h"
#include "taccesslevel.h"
#include "tclientinfo.h"
#include "tcompilationresult.h"
#include "tcompiledproject.h"
#include "tcompilerparameters.h"
#include "tinviteinfo.h"
#include "toperationresult.h"
#include "tproject.h"
#include "tprojectfile.h"
#include "tsampleinfo.h"
#include "tnamespace.h"
#include "tuserinfo.h"
#include "tprojectfilelist.h"

#include <QMetaType>

void tRegister()
{
    static bool registered = false;
    if (registered)
        return;
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_INIT_RESOURCE(texsample);
    Q_INIT_RESOURCE(texsample_translations);
#endif
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
    qRegisterMetaType<TInviteInfo>();
    qRegisterMetaTypeStreamOperators<TInviteInfo>();
    qRegisterMetaType<TInviteInfo::InvitesList>();
    qRegisterMetaTypeStreamOperators<TInviteInfo::InvitesList>();
    qRegisterMetaType<TOperationResult>();
    qRegisterMetaTypeStreamOperators<TOperationResult>();
    qRegisterMetaType<TProject>();
    qRegisterMetaTypeStreamOperators<TProject>();
    qRegisterMetaType<TProjectFile>();
    qRegisterMetaTypeStreamOperators<TProjectFile>();
    qRegisterMetaType<TSampleInfo>();
    qRegisterMetaTypeStreamOperators<TSampleInfo>();
    qRegisterMetaType<TSampleInfo::SamplesList>();
    qRegisterMetaTypeStreamOperators<TSampleInfo::SamplesList>();
    qRegisterMetaType<Texsample::IdList>();
    qRegisterMetaTypeStreamOperators<Texsample::IdList>();
    qRegisterMetaType<TUserInfo>();
    qRegisterMetaTypeStreamOperators<TUserInfo>();
    qRegisterMetaType<TProjectFileList>();
    qRegisterMetaTypeStreamOperators<TProjectFileList>();
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
    return "0.2.2";
}
