#ifndef TNAMESPACE_H
#define TNAMESPACE_H

#include <BeQt>

#include <QString>
#include <QtGlobal>
#include <QMetaType>

namespace Texsample
{

const quint16 MainPort = 9044;

const qint64 MaximumAvatarSize = BeQt::Megabyte;
const quint8 MaximumInvitesCount = 3;

//Requests
const QString RegisterRequest = "register";
const QString AuthorizeRequest = "authorize";
const QString AddUserRequest = "add_user";
const QString EditUserRequest = "edit_user";
const QString UpdateAccountRequest = "update_account";
const QString GetRecoveryCodeRequest = "get_recovery_code";
const QString RecoverAccountRequest = "recover_account";
const QString GetUserInfoRequest = "get_user_info";
const QString AddSampleRequest = "add_sample";
const QString EditSampleRequest = "edit_sample";
const QString UpdateSampleRequest = "update_sample";
const QString DeleteSampleRequest = "delete_sample";
const QString GetSamplesListRequest = "get_samples_list";
const QString GetSampleSourceRequest = "get_sample_source";
const QString GetSamplePreviewRequest = "get_sample_preview";
const QString GenerateInvitesRequest = "generate_invites";
const QString GetInvitesListRequest = "get_invites_list";
const QString CompileProjectRequest = "compile_project";
const QString SubscribeRequest = "subscribe";
const QString ChangeLocaleRequest = "change_locale";

const QString LogRequest = "log";
const QString MessageRequest = "message";

}

#endif // TNAMESPACE_H
