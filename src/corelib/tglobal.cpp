/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleCore module of the TeXSample library.
**
** TeXSample is free software: you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** TeXSample is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with TeXSample.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "tglobal.h"

#include "reply/taddgroupreplydata.h"
#include "reply/taddlabreplydata.h"
#include "reply/taddsamplereplydata.h"
#include "reply/tadduserreplydata.h"
#include "reply/tauthorizereplydata.h"
#include "reply/tchangeemailreplydata.h"
#include "reply/tchangepasswordreplydata.h"
#include "reply/tcheckemailavailabilityreplydata.h"
#include "reply/tcheckloginavailabilityreplydata.h"
#include "reply/tcompiletexprojectreplydata.h"
#include "reply/tconfirmemailchangereplydata.h"
#include "reply/tconfirmregistrationreplydata.h"
#include "reply/tdeletegroupreplydata.h"
#include "reply/tdeleteinvitesreplydata.h"
#include "reply/tdeletelabreplydata.h"
#include "reply/tdeletesamplereplydata.h"
#include "reply/tdeleteuserreplydata.h"
#include "reply/teditgroupreplydata.h"
#include "reply/teditlabreplydata.h"
#include "reply/teditsampleadminreplydata.h"
#include "reply/teditsamplereplydata.h"
#include "reply/teditselfreplydata.h"
#include "reply/tedituserreplydata.h"
#include "reply/tgenerateinvitesreplydata.h"
#include "reply/tgetgroupinfolistreplydata.h"
#include "reply/tgetinviteinfolistreplydata.h"
#include "reply/tgetlabdatareplydata.h"
#include "reply/tgetlabextrafilereplydata.h"
#include "reply/tgetlabinfolistreplydata.h"
#include "reply/tgetlatestappversionreplydata.h"
#include "reply/tgetsampleinfolistreplydata.h"
#include "reply/tgetsamplepreviewreplydata.h"
#include "reply/tgetsamplesourcereplydata.h"
#include "reply/tgetselfinforeplydata.h"
#include "reply/tgetserverstatereplydata.h"
#include "reply/tgetuserconnectioninfolistreplydata.h"
#include "reply/tgetuserinfoadminreplydata.h"
#include "reply/tgetuserinfolistadminreplydata.h"
#include "reply/tgetuserinforeplydata.h"
#include "reply/tlogreplydata.h"
#include "reply/trecoveraccountreplydata.h"
#include "reply/tregisterreplydata.h"
#include "reply/treply.h"
#include "reply/trequestrecoverycodereplydata.h"
#include "reply/tsetlatestappversionreplydata.h"
#include "reply/tsetserverstatereplydata.h"
#include "reply/tsubscribereplydata.h"
#include "request/taddgrouprequestdata.h"
#include "request/taddlabrequestdata.h"
#include "request/taddsamplerequestdata.h"
#include "request/tadduserrequestdata.h"
#include "request/tauthorizerequestdata.h"
#include "request/tchangeemailrequestdata.h"
#include "request/tchangepasswordrequestdata.h"
#include "request/tcheckemailavailabilityrequestdata.h"
#include "request/tcheckloginavailabilityrequestdata.h"
#include "request/tcompiletexprojectrequestdata.h"
#include "request/tconfirmemailchangerequestdata.h"
#include "request/tconfirmregistrationrequestdata.h"
#include "request/tdeletegrouprequestdata.h"
#include "request/tdeleteinvitesrequestdata.h"
#include "request/tdeletelabrequestdata.h"
#include "request/tdeletesamplerequestdata.h"
#include "request/tdeleteuserrequestdata.h"
#include "request/teditgrouprequestdata.h"
#include "request/teditlabrequestdata.h"
#include "request/teditsampleadminrequestdata.h"
#include "request/teditsamplerequestdata.h"
#include "request/teditselfrequestdata.h"
#include "request/tedituserrequestdata.h"
#include "request/tgenerateinvitesrequestdata.h"
#include "request/tgetgroupinfolistrequestdata.h"
#include "request/tgetinviteinfolistrequestdata.h"
#include "request/tgetlabdatarequestdata.h"
#include "request/tgetlabextrafilerequestdata.h"
#include "request/tgetlabinfolistrequestdata.h"
#include "request/tgetlatestappversionrequestdata.h"
#include "request/tgetsampleinfolistrequestdata.h"
#include "request/tgetsamplepreviewrequestdata.h"
#include "request/tgetsamplesourcerequestdata.h"
#include "request/tgetselfinforequestdata.h"
#include "request/tgetserverstaterequestdata.h"
#include "request/tgetuserconnectioninfolistrequestdata.h"
#include "request/tgetuserinfoadminrequestdata.h"
#include "request/tgetuserinfolistadminrequestdata.h"
#include "request/tgetuserinforequestdata.h"
#include "request/tlogrequestdata.h"
#include "request/trecoveraccountrequestdata.h"
#include "request/tregisterrequestdata.h"
#include "request/trequest.h"
#include "request/trequestrecoverycoderequestdata.h"
#include "request/tsetlatestappversionrequestdata.h"
#include "request/tsetserverstaterequestdata.h"
#include "request/tsubscriberequestdata.h"
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
#include "tlabapplication.h"
#include "tlabdata.h"
#include "tlabdatainfo.h"
#include "tlabdatainfolist.h"
#include "tlabdatalist.h"
#include "tlabinfo.h"
#include "tlabinfolist.h"
#include "tlabtype.h"
#include "tsampleinfo.h"
#include "tsampleinfolist.h"
#include "tsampletype.h"
#include "tserverstate.h"
#include "tservice.h"
#include "tservicelist.h"
#include "ttexcompiler.h"
#include "ttexfile.h"
#include "ttexfilelist.h"
#include "ttexproject.h"
#include "tuserconnectioninfo.h"
#include "tuserconnectioninfolist.h"
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
    qRegisterMetaType<TAddLabReplyData>();
    qRegisterMetaTypeStreamOperators<TAddLabReplyData>();
    qRegisterMetaType<TAddSampleReplyData>();
    qRegisterMetaTypeStreamOperators<TAddSampleReplyData>();
    qRegisterMetaType<TAddUserReplyData>();
    qRegisterMetaTypeStreamOperators<TAddUserReplyData>();
    qRegisterMetaType<TChangeEmailReplyData>();
    qRegisterMetaTypeStreamOperators<TAuthorizeReplyData>();
    qRegisterMetaType<TAuthorizeReplyData>();
    qRegisterMetaTypeStreamOperators<TChangeEmailReplyData>();
    qRegisterMetaType<TChangePasswordReplyData>();
    qRegisterMetaTypeStreamOperators<TChangePasswordReplyData>();
    qRegisterMetaType<TCheckEmailAvailabilityReplyData>();
    qRegisterMetaTypeStreamOperators<TCheckEmailAvailabilityReplyData>();
    qRegisterMetaType<TCheckLoginAvailabilityReplyData>();
    qRegisterMetaTypeStreamOperators<TCheckLoginAvailabilityReplyData>();
    qRegisterMetaType<TCompileTexProjectReplyData>();
    qRegisterMetaTypeStreamOperators<TCompileTexProjectReplyData>();
    qRegisterMetaType<TConfirmEmailChangeReplyData>();
    qRegisterMetaTypeStreamOperators<TConfirmEmailChangeReplyData>();
    qRegisterMetaType<TConfirmRegistrationReplyData>();
    qRegisterMetaTypeStreamOperators<TConfirmRegistrationReplyData>();
    qRegisterMetaType<TDeleteGroupReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteGroupReplyData>();
    qRegisterMetaType<TDeleteInvitesReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteInvitesReplyData>();
    qRegisterMetaType<TDeleteLabReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteLabReplyData>();
    qRegisterMetaType<TDeleteSampleReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteSampleReplyData>();
    qRegisterMetaType<TDeleteUserReplyData>();
    qRegisterMetaTypeStreamOperators<TDeleteUserReplyData>();
    qRegisterMetaType<TEditGroupReplyData>();
    qRegisterMetaTypeStreamOperators<TEditGroupReplyData>();
    qRegisterMetaType<TEditLabReplyData>();
    qRegisterMetaTypeStreamOperators<TEditLabReplyData>();
    qRegisterMetaType<TEditSampleAdminReplyData>();
    qRegisterMetaTypeStreamOperators<TEditSampleAdminReplyData>();
    qRegisterMetaType<TEditSampleReplyData>();
    qRegisterMetaTypeStreamOperators<TEditSampleReplyData>();
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
    qRegisterMetaType<TGetLabDataReplyData>();
    qRegisterMetaTypeStreamOperators<TGetLabDataReplyData>();
    qRegisterMetaType<TGetLabExtraFileReplyData>();
    qRegisterMetaTypeStreamOperators<TGetLabExtraFileReplyData>();
    qRegisterMetaType<TGetLabInfoListReplyData>();
    qRegisterMetaTypeStreamOperators<TGetLabInfoListReplyData>();
    qRegisterMetaType<TGetLatestAppVersionReplyData>();
    qRegisterMetaTypeStreamOperators<TGetLatestAppVersionReplyData>();
    qRegisterMetaType<TGetSampleInfoListReplyData>();
    qRegisterMetaTypeStreamOperators<TGetSampleInfoListReplyData>();
    qRegisterMetaType<TGetSamplePreviewReplyData>();
    qRegisterMetaTypeStreamOperators<TGetSamplePreviewReplyData>();
    qRegisterMetaType<TGetSampleSourceReplyData>();
    qRegisterMetaTypeStreamOperators<TGetSampleSourceReplyData>();
    qRegisterMetaType<TGetSelfInfoReplyData>();
    qRegisterMetaTypeStreamOperators<TGetSelfInfoReplyData>();
    qRegisterMetaType<TGetServerStateReplyData>();
    qRegisterMetaTypeStreamOperators<TGetServerStateReplyData>();
    qRegisterMetaType<TGetUserConnectionInfoListReplyData>();
    qRegisterMetaTypeStreamOperators<TGetUserConnectionInfoListReplyData>();
    qRegisterMetaType<TGetUserInfoAdminReplyData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoAdminReplyData>();
    qRegisterMetaType<TGetUserInfoListAdminReplyData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoListAdminReplyData>();
    qRegisterMetaType<TGetUserInfoReplyData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoReplyData>();
    qRegisterMetaType<TLogReplyData>();
    qRegisterMetaTypeStreamOperators<TLogReplyData>();
    qRegisterMetaType<TRecoverAccountReplyData>();
    qRegisterMetaTypeStreamOperators<TRecoverAccountReplyData>();
    qRegisterMetaType<TRegisterReplyData>();
    qRegisterMetaTypeStreamOperators<TRegisterReplyData>();
    qRegisterMetaType<TReply>();
    qRegisterMetaTypeStreamOperators<TReply>();
    qRegisterMetaType<TRequestRecoveryCodeReplyData>();
    qRegisterMetaTypeStreamOperators<TRequestRecoveryCodeReplyData>();
    qRegisterMetaType<TSetLatestAppVersionReplyData>();
    qRegisterMetaTypeStreamOperators<TSetLatestAppVersionReplyData>();
    qRegisterMetaType<TSetServerStateReplyData>();
    qRegisterMetaTypeStreamOperators<TSetServerStateReplyData>();
    qRegisterMetaType<TSubscribeReplyData>();
    qRegisterMetaTypeStreamOperators<TSubscribeReplyData>();
    //Requests
    qRegisterMetaType<TAddGroupRequestData>();
    qRegisterMetaTypeStreamOperators<TAddGroupRequestData>();
    qRegisterMetaType<TAddLabRequestData>();
    qRegisterMetaTypeStreamOperators<TAddLabRequestData>();
    qRegisterMetaType<TAddSampleRequestData>();
    qRegisterMetaTypeStreamOperators<TAddSampleRequestData>();
    qRegisterMetaType<TAddUserRequestData>();
    qRegisterMetaTypeStreamOperators<TAddUserRequestData>();
    qRegisterMetaType<TAuthorizeRequestData>();
    qRegisterMetaTypeStreamOperators<TAuthorizeRequestData>();
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
    qRegisterMetaType<TConfirmEmailChangeRequestData>();
    qRegisterMetaTypeStreamOperators<TConfirmEmailChangeRequestData>();
    qRegisterMetaType<TConfirmRegistrationRequestData>();
    qRegisterMetaTypeStreamOperators<TConfirmRegistrationRequestData>();
    qRegisterMetaType<TDeleteGroupRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteGroupRequestData>();
    qRegisterMetaType<TDeleteInvitesRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteInvitesRequestData>();
    qRegisterMetaType<TDeleteLabRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteLabRequestData>();
    qRegisterMetaType<TDeleteSampleRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteSampleRequestData>();
    qRegisterMetaType<TDeleteUserRequestData>();
    qRegisterMetaTypeStreamOperators<TDeleteUserRequestData>();
    qRegisterMetaType<TEditGroupRequestData>();
    qRegisterMetaTypeStreamOperators<TEditGroupRequestData>();
    qRegisterMetaType<TEditLabRequestData>();
    qRegisterMetaTypeStreamOperators<TEditLabRequestData>();
    qRegisterMetaType<TEditSampleAdminRequestData>();
    qRegisterMetaTypeStreamOperators<TEditSampleAdminRequestData>();
    qRegisterMetaType<TEditSampleRequestData>();
    qRegisterMetaTypeStreamOperators<TEditSampleRequestData>();
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
    qRegisterMetaType<TGetLabDataRequestData>();
    qRegisterMetaTypeStreamOperators<TGetLabDataRequestData>();
    qRegisterMetaType<TGetLabExtraFileRequestData>();
    qRegisterMetaTypeStreamOperators<TGetLabExtraFileRequestData>();
    qRegisterMetaType<TGetLabInfoListRequestData>();
    qRegisterMetaTypeStreamOperators<TGetLabInfoListRequestData>();
    qRegisterMetaType<TGetLatestAppVersionRequestData>();
    qRegisterMetaTypeStreamOperators<TGetLatestAppVersionRequestData>();
    qRegisterMetaType<TGetSampleInfoListRequestData>();
    qRegisterMetaTypeStreamOperators<TGetSampleInfoListRequestData>();
    qRegisterMetaType<TGetSamplePreviewRequestData>();
    qRegisterMetaTypeStreamOperators<TGetSamplePreviewRequestData>();
    qRegisterMetaType<TGetSampleSourceRequestData>();
    qRegisterMetaTypeStreamOperators<TGetSampleSourceRequestData>();
    qRegisterMetaType<TGetSelfInfoRequestData>();
    qRegisterMetaTypeStreamOperators<TGetSelfInfoRequestData>();
    qRegisterMetaType<TGetServerStateRequestData>();
    qRegisterMetaTypeStreamOperators<TGetServerStateRequestData>();
    qRegisterMetaType<TGetUserConnectionInfoListRequestData>();
    qRegisterMetaTypeStreamOperators<TGetUserConnectionInfoListRequestData>();
    qRegisterMetaType<TGetUserInfoAdminRequestData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoAdminRequestData>();
    qRegisterMetaType<TGetUserInfoListAdminRequestData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoListAdminRequestData>();
    qRegisterMetaType<TGetUserInfoRequestData>();
    qRegisterMetaTypeStreamOperators<TGetUserInfoRequestData>();
    qRegisterMetaType<TLogRequestData>();
    qRegisterMetaTypeStreamOperators<TLogRequestData>();
    qRegisterMetaType<TRecoverAccountRequestData>();
    qRegisterMetaTypeStreamOperators<TRecoverAccountRequestData>();
    qRegisterMetaType<TRegisterRequestData>();
    qRegisterMetaTypeStreamOperators<TRegisterRequestData>();
    qRegisterMetaType<TRequest>();
    qRegisterMetaTypeStreamOperators<TRequest>();
    qRegisterMetaType<TRequestRecoveryCodeRequestData>();
    qRegisterMetaTypeStreamOperators<TRequestRecoveryCodeRequestData>();
    qRegisterMetaType<TSetLatestAppVersionRequestData>();
    qRegisterMetaTypeStreamOperators<TSetLatestAppVersionRequestData>();
    qRegisterMetaType<TSetServerStateRequestData>();
    qRegisterMetaTypeStreamOperators<TSetServerStateRequestData>();
    qRegisterMetaType<TSubscribeRequestData>();
    qRegisterMetaTypeStreamOperators<TSubscribeRequestData>();
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
    qRegisterMetaType<TLabApplication>();
    qRegisterMetaTypeStreamOperators<TLabApplication>();
    qRegisterMetaType<TLabInfo>();
    qRegisterMetaTypeStreamOperators<TLabInfo>();
    qRegisterMetaType<TLabInfoList>();
    qRegisterMetaTypeStreamOperators<TLabInfoList>();
    qRegisterMetaType<TLabType>();
    qRegisterMetaTypeStreamOperators<TLabType>();
    qRegisterMetaType<TLabData>();
    qRegisterMetaTypeStreamOperators<TLabData>();
    qRegisterMetaType<TLabDataInfo>();
    qRegisterMetaTypeStreamOperators<TLabDataInfo>();
    qRegisterMetaType<TLabDataInfoList>();
    qRegisterMetaTypeStreamOperators<TLabDataInfoList>();
    qRegisterMetaType<TLabDataList>();
    qRegisterMetaTypeStreamOperators<TLabDataList>();
    qRegisterMetaType<TSampleInfo>();
    qRegisterMetaTypeStreamOperators<TSampleInfo>();
    qRegisterMetaType<TSampleInfoList>();
    qRegisterMetaTypeStreamOperators<TSampleInfoList>();
    qRegisterMetaType<TSampleType>();
    qRegisterMetaTypeStreamOperators<TSampleType>();
    qRegisterMetaType<TServerState>();
    qRegisterMetaTypeStreamOperators<TServerState>();
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
    qRegisterMetaType<TUserConnectionInfo>();
    qRegisterMetaTypeStreamOperators<TUserConnectionInfo>();
    qRegisterMetaType<TUserConnectionInfoList>();
    qRegisterMetaTypeStreamOperators<TUserConnectionInfoList>();
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
    return "2.0.0-beta6";
}
