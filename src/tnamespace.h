#ifndef TNAMESPACE_H
#define TNAMESPACE_H

#include <QString>
#include <QtGlobal>
#include <QList>
#include <QMetaType>

namespace Texsample
{

typedef QList<quint64> IdList;

const QString RegisterRequest = "register";
const QString AuthorizeRequest = "authorize";
const QString AddUserRequest = "add_user";
const QString EditUserRequest = "edit_user";
const QString UpdateAccountRequest = "update_account";
const QString GetUserInfoRequest = "get_user_info";
const QString AddSampleRequest = "add_sample";
const QString EditSampleRequest = "edit_sample";
const QString DeleteSampleRequest = "delete_sample";
const QString GetSamplesListRequest = "get_samples_list";
const QString GetSampleSourceRequest = "get_sample_source";
const QString GetSamplePreviewRequest = "get_sample_preview";
const QString GenerateInvitesRequest = "generate_invites";
const QString GetInvitesListRequest = "get_invites_list";
const QString CompileProjectRequest = "compile_project";

}

Q_DECLARE_METATYPE(Texsample::IdList)

#endif // TNAMESPACE_H
