#include "tglobal.h"

#include "reply/taddgroupreplydata.h"
#include "reply/tadduserreplydata.h"
#include "reply/tchangeemailreplydata.h"
#include "reply/tchangepasswordreplydata.h"
#include "reply/tcheckemailavailabilityreplydata.h"
#include "reply/tcheckloginavailabilityreplydata.h"
#include "reply/tcompiletexprojectreplydata.h"
#include "reply/tdeletegroupreplydata.h"
#include "reply/tdeleteinvitesreplydata.h"
#include "reply/tdeleteuserreplydata.h"
#include "reply/teditgroupreplydata.h"
#include "reply/teditselfreplydata.h"
#include "reply/tedituserreplydata.h"
#include "reply/tgenerateinvitesreplydata.h"
#include "reply/tgetgroupinfolistreplydata.h"
#include "reply/tgetinviteinfolistreplydata.h"
#include "reply/tgetselfinforeplydata.h"
#include "reply/tgetuseravatarreplydata.h"
#include "reply/tgetuserinfoadminreplydata.h"
#include "reply/tgetuserinforeplydata.h"
#include "reply/trecoveraccountreplydata.h"
#include "reply/tregisterreplydata.h"
#include "reply/treply.h"
#include "reply/trequestrecoverycodereplydata.h"
#include "request/taddgrouprequestdata.h"
#include "request/tadduserrequestdata.h"
#include "request/tchangeemailrequestdata.h"
#include "request/tchangepasswordrequestdata.h"
#include "request/tcheckemailavailabilityrequestdata.h"
#include "request/tcheckloginavailabilityrequestdata.h"
#include "request/tcompiletexprojectrequestdata.h"
#include "request/tdeletegrouprequestdata.h"
#include "request/tdeleteinvitesrequestdata.h"
#include "request/tdeleteuserrequestdata.h"
#include "request/teditgrouprequestdata.h"
#include "request/teditselfrequestdata.h"
#include "request/tedituserrequestdata.h"
#include "request/tgenerateinvitesrequestdata.h"
#include "request/tgetgroupinfolistrequestdata.h"
#include "request/tgetinviteinfolistrequestdata.h"
#include "request/tgetselfinforequestdata.h"
#include "request/tgetuseravatarrequestdata.h"
#include "request/tgetuserinfoadminrequestdata.h"
#include "request/tgetuserinforequestdata.h"
#include "request/trecoveraccountrequestdata.h"
#include "request/tregisterrequestdata.h"
#include "request/trequest.h"
#include "request/trequestrecoverycoderequestdata.h"
#include "taccesslevel.h"
#include "tauthorinfo.h"
#include "tauthorinfolist.h"
#include "tbinaryfile.h"
#include "tbinaryfilelist.h"
#include "tclientinfo.h"
#include "tfileinfo.h"
#include "tfileinfolist.h"
#include "tgroupinfo.h"
#include "tgroupinfolist.h"
#include "tidlist.h"
#include "tinviteinfo.h"
#include "tinviteinfolist.h"
#include "tlabdata.h"
#include "tlabdatainfo.h"
#include "tlabdatainfolist.h"
#include "tlabinfo.h"
#include "tlabinfolist.h"
#include "tlabtype.h"
#include "tmessage.h"
#include "tsampleinfo.h"
#include "tsampleinfolist.h"
#include "tsampletype.h"
#include "tservice.h"
#include "tservicelist.h"
#include "ttexcompiler.h"
#include "ttexfile.h"
#include "ttexfilelist.h"
#include "ttexproject.h"
#include "tuseridentifier.h"
#include "tuserinfo.h"
#include "tuserinfolist.h"

#include <BeQtGlobal>

#include <QMetaType>

void tRegister()
{
    static bool registered = false;
    if (registered)
        return;
    bRegister();
    //Replies
    qRegisterMetaType<TAddGroupReplyData>();
    qRegisterMetaTypeStreamOperators<TAddGroupReplyData>();
    qRegisterMetaType<TAddUserReplyData>();
    qRegisterMetaTypeStreamOperators<TAddUserReplyData>();
    qRegisterMetaType<TChangeEmailReplyData>();
    qRegisterMetaTypeStreamOperators<TChangeEmailReplyData>();
    qRegisterMetaType<TChangePasswordReplyData>();
    qRegisterMetaTypeStreamOperators<TChangePasswordReplyData>();
    qRegisterMetaType<TCheckEmailAvailabilityReplyData>();
    qRegisterMetaTypeStreamOperators<TCheckEmailAvailabilityReplyData>();
    qRegisterMetaType<TCheckLoginAvailabilityReplyData>();
    qRegisterMetaTypeStreamOperators<TCheckLoginAvailabilityReplyData>();
    qRegisterMetaType<TCompileTexProjectReplyData>();
    qRegisterMetaTypeStreamOperators<TCompileTexProjectReplyData>();
    qRegisterMetaType<TDeleteGroupReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteGroupReplyData>();
    qRegisterMetaType<TDeleteInvitesReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteInvitesReplyData>();
    qRegisterMetaType<TDeleteUserReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteUserReplyData>();
    qRegisterMetaType<TEditGroupReplyData>();
    qRegisterMetaTypeStreamOperators<TEditGroupReplyData>();
    qRegisterMetaType<TEditSelfReplyData>();
    qRegisterMetaTypeStreamOperators<TEditSelfReplyData>();
    qRegisterMetaType<TEditUserReplyData>();
    qRegisterMetaTypeStreamOperators<TEditUserReplyData>();
    qRegisterMetaType<TGenerateInvitesReplyData>();
    qRegisterMetaTypeStreamOperators<TGenerateInvitesReplyData>();
    qRegisterMetaType<TGetGroupInfoListReplyData>();
    qRegisterMetaTypeStreamOperators<TGetGroupInfoListReplyData>();
    qRegisterMetaType<TGetInviteInfoListReplyData>();
    qRegisterMetaTypeStreamOperators<TGetInviteInfoListReplyData>();
    qRegisterMetaType<TGetSelfInfoRequestData>();
    qRegisterMetaTypeStreamOperators<TGetSelfInfoRequestData>();
    qRegisterMetaType<TGetUserAvatarReplyData>();
    qRegisterMetaTypeStreamOperators<TGetUserAvatarReplyData>();
    qRegisterMetaType<TGetUserInfoAdminReplyData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoAdminReplyData>();
    qRegisterMetaType<TGetUserInfoReplyData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoReplyData>();
    qRegisterMetaType<TRecoverAccountReplyData>();
    qRegisterMetaTypeStreamOperators<TRecoverAccountReplyData>();
    qRegisterMetaType<TRegisterReplyData>();
    qRegisterMetaTypeStreamOperators<TRegisterReplyData>();
    qRegisterMetaType<TReply>();
    qRegisterMetaTypeStreamOperators<TReply>();
    qRegisterMetaType<TRequestRecoveryCodeReplyData>();
    qRegisterMetaTypeStreamOperators<TRequestRecoveryCodeReplyData>();
    //Requests
    qRegisterMetaType<TAddGroupRequestData>();
    qRegisterMetaTypeStreamOperators<TAddGroupRequestData>();
    qRegisterMetaType<TAddUserRequestData>();
    qRegisterMetaTypeStreamOperators<TAddUserRequestData>();
    qRegisterMetaType<TChangeEmailRequestData>();
    qRegisterMetaTypeStreamOperators<TChangeEmailRequestData>();
    qRegisterMetaType<TChangePasswordRequestData>();
    qRegisterMetaTypeStreamOperators<TChangePasswordRequestData>();
    qRegisterMetaType<TCheckEmailAvailabilityRequestData>();
    qRegisterMetaTypeStreamOperators<TCheckEmailAvailabilityRequestData>();
    qRegisterMetaType<TCheckLoginAvailabilityRequestData>();
    qRegisterMetaTypeStreamOperators<TCheckLoginAvailabilityRequestData>();
    qRegisterMetaType<TCompileTexProjectRequestData>();
    qRegisterMetaTypeStreamOperators<TCompileTexProjectRequestData>();
    qRegisterMetaType<TDeleteGroupRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteGroupRequestData>();
    qRegisterMetaType<TDeleteInvitesRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteInvitesRequestData>();
    qRegisterMetaType<TDeleteUserRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteUserRequestData>();
    qRegisterMetaType<TEditGroupRequestData>();
    qRegisterMetaTypeStreamOperators<TEditGroupRequestData>();
    qRegisterMetaType<TEditSelfRequestData>();
    qRegisterMetaTypeStreamOperators<TEditSelfRequestData>();
    qRegisterMetaType<TEditUserRequestData>();
    qRegisterMetaTypeStreamOperators<TEditUserRequestData>();
    qRegisterMetaType<TGenerateInvitesRequestData>();
    qRegisterMetaTypeStreamOperators<TGenerateInvitesRequestData>();
    qRegisterMetaType<TGetGroupInfoListRequestData>();
    qRegisterMetaTypeStreamOperators<TGetGroupInfoListRequestData>();
    qRegisterMetaType<TGetInviteInfoListRequestData>();
    qRegisterMetaTypeStreamOperators<TGetInviteInfoListRequestData>();
    qRegisterMetaType<TGetSelfInfoRequestData>();
    qRegisterMetaTypeStreamOperators<TGetSelfInfoRequestData>();
    qRegisterMetaType<TGetUserAvatarRequestData>();
    qRegisterMetaTypeStreamOperators<TGetUserAvatarRequestData>();
    qRegisterMetaType<TGetUserInfoAdminRequestData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoAdminRequestData>();
    qRegisterMetaType<TGetUserInfoRequestData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoRequestData>();
    qRegisterMetaType<TRecoverAccountRequestData>();
    qRegisterMetaTypeStreamOperators<TRecoverAccountRequestData>();
    qRegisterMetaType<TRegisterRequestData>();
    qRegisterMetaTypeStreamOperators<TRegisterRequestData>();
    qRegisterMetaType<TRequest>();
    qRegisterMetaTypeStreamOperators<TRequest>();
    qRegisterMetaType<TRequestRecoveryCodeRequestData>();
    qRegisterMetaTypeStreamOperators<TRequestRecoveryCodeRequestData>();
    //Global
    qRegisterMetaType<TAccessLevel>();
    qRegisterMetaTypeStreamOperators<TAccessLevel>();
    qRegisterMetaType<TAuthorInfo>();
    qRegisterMetaTypeStreamOperators<TAuthorInfo>();
    qRegisterMetaType<TAuthorInfoList>();
    qRegisterMetaTypeStreamOperators<TAuthorInfoList>();
    qRegisterMetaType<TBinaryFile>();
    qRegisterMetaTypeStreamOperators<TBinaryFile>();
    qRegisterMetaType<TBinaryFileList>();
    qRegisterMetaTypeStreamOperators<TBinaryFileList>();
    qRegisterMetaType<TClientInfo>();
    qRegisterMetaTypeStreamOperators<TClientInfo>();
    qRegisterMetaType<TFileInfo>();
    qRegisterMetaTypeStreamOperators<TFileInfo>();
    qRegisterMetaType<TFileInfoList>();
    qRegisterMetaTypeStreamOperators<TFileInfoList>();
    qRegisterMetaType<TGroupInfo>();
    qRegisterMetaTypeStreamOperators<TGroupInfo>();
    qRegisterMetaType<TGroupInfoList>();
    qRegisterMetaTypeStreamOperators<TGroupInfoList>();
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
    qRegisterMetaType<TLabType>();
    qRegisterMetaTypeStreamOperators<TLabType>();
    qRegisterMetaType<TMessage>();
    qRegisterMetaTypeStreamOperators<TMessage>();
    qRegisterMetaType<TLabData>();
    qRegisterMetaTypeStreamOperators<TLabData>();
    qRegisterMetaType<TLabDataInfo>();
    qRegisterMetaTypeStreamOperators<TLabDataInfo>();
    qRegisterMetaType<TLabDataInfoList>();
    qRegisterMetaTypeStreamOperators<TLabDataInfoList>();
    qRegisterMetaType<TSampleInfo>();
    qRegisterMetaTypeStreamOperators<TSampleInfo>();
    qRegisterMetaType<TSampleInfoList>();
    qRegisterMetaTypeStreamOperators<TSampleInfoList>();
    qRegisterMetaType<TSampleType>();
    qRegisterMetaTypeStreamOperators<TSampleType>();
    qRegisterMetaType<TService>();
    qRegisterMetaTypeStreamOperators<TService>();
    qRegisterMetaType<TServiceList>();
    qRegisterMetaTypeStreamOperators<TServiceList>();
    qRegisterMetaType<TTexCompiler>();
    qRegisterMetaTypeStreamOperators<TTexCompiler>();
    qRegisterMetaType<TTexFile>();
    qRegisterMetaTypeStreamOperators<TTexFile>();
    qRegisterMetaType<TTexFileList>();
    qRegisterMetaTypeStreamOperators<TTexFileList>();
    qRegisterMetaType<TTexProject>();
    qRegisterMetaTypeStreamOperators<TTexProject>();
    qRegisterMetaType<TUserIdentifier>();
    qRegisterMetaTypeStreamOperators<TUserIdentifier>();
    qRegisterMetaType<TUserInfo>();
    qRegisterMetaTypeStreamOperators<TUserInfo>();
    qRegisterMetaType<TUserInfoList>();
    qRegisterMetaTypeStreamOperators<TUserInfoList>();
    registered = true;
}

const char *tVersion()
{
    return "2.0.0-beta";
}
