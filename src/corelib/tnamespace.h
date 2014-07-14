#ifndef TNAMESPACE_H
#define TNAMESPACE_H

class QImage;

#include "tglobal.h"

#include <BeQt>

#include <QString>
#include <QtGlobal>
#include <QMetaType>

namespace Texsample
{

const quint16 MainPort = 9044;

//const int MaximumAvatarSize = BeQt::Megabyte;
//const int MaximumAvatarExtent = 2048;
const quint8 MaximumInvitesCount = 3;

//Requests
const QString CheckEmailRequest = "check_email";
const QString CheckLoginRequest = "check_login";
const QString RegisterRequest = "register";
const QString GetRecoveryCodeRequest = "get_recovery_code";
const QString RecoverAccountRequest = "recover_account";
const QString GetLatestAppVersionRequest = "get_latest_version";
const QString AuthorizeRequest = "authorize";
const QString AddUserRequest = "add_user";
const QString EditUserRequest = "edit_user";
const QString UpdateAccountRequest = "update_account";
const QString GetUserInfoRequest = "get_user_info";
const QString GenerateInvitesRequest = "generate_invites";
const QString GetInvitesListRequest = "get_invites_list";
const QString SubscribeRequest = "subscribe";
const QString ChangeLocaleRequest = "change_locale";
const QString StartServerRequest = "start_server";
const QString StopServerRequest = "stop_server";
const QString UptimeRequest = "uptime";
const QString UserRequest = "user";
const QString SetLatestAppVersionRequest = "set_latest_app_version";

const QString LogRequest = "log";
const QString MessageRequest = "message";
const QString NotifyRequest = "notify";

//TeXSample requests
const QString AddSampleRequest = "add_sample";
const QString EditSampleRequest = "edit_sample";
const QString UpdateSampleRequest = "update_sample";
const QString DeleteSampleRequest = "delete_sample";
const QString GetSamplesListRequest = "get_samples_list";
const QString GetSampleSourceRequest = "get_sample_source";
const QString GetSamplePreviewRequest = "get_sample_preview";
const QString CompileProjectRequest = "compile_project";

//CLab requests
const QString EditClabGroupsRequest = "edit_clab_groups";
const QString GetClabGroupsListRequest = "get_clab_groups_list";
const QString AddLabRequest = "add_lab";
const QString EditLabRequest = "edit_lab";
const QString DeleteLabRequest = "delete_lab";
const QString GetLabRequest = "get_lab";
const QString GetLabsListRequest = "get_labs_list";
const QString GetLabExtraAttachedFileRequest = "get_lab_extra_attached_file";

const int MaximumAvatarExtent = 2000;
const int MaximumAvatarSize = 2 * BeQt::Megabyte;
const int MaximumEmailLength = 60;
const int MaximumFileDescriptionLength = 1000;
const int MaximumLoginLength = 20;
const int MinimumLoginLength = 2;
const int MaximumNameLength = 20;
const int MaximumPasswordLength = 20;
const int MinimumPasswordLength = 8;
const int MaximumGroupNameLength = 40;

T_CORE_EXPORT bool testAvatar(const QImage &avatar, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QString &avatarFileName, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QString &avatarFileName, QImage *image, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testEmail(const QString &email, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testFileDescription(const QString &desctiption, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testLogin(const QString &login, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testName(const QString &name, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testPassword(const QString &password, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testGroupName(const QString &name, QString *error = 0, bool translate = true);

}

#endif // TNAMESPACE_H
