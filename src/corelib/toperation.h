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

#ifndef TOPERATION_H
#define TOPERATION_H

#include <QString>

namespace TOperation
{

const QString AddGroup = "add_group";
const QString AddLab = "add_lab";
const QString AddSample = "add_sample";
const QString AddUser = "add_user";
const QString Authorize = "authorize";
const QString ChangeEmail = "change_email";
const QString ChangePassword = "change_password";
const QString CheckEmailAvailability = "check_email_availability";
const QString CheckLoginAvailability = "check_login_availability";
const QString CompileTexProject = "compile_tex_project";
const QString ConfirmRegistration = "confirm_registration";
const QString DeleteGroup = "delete_group";
const QString DeleteInvites = "delete_invites";
const QString DeleteLab = "delete_lab";
const QString DeleteSample = "delete_sample";
const QString DeleteUser = "delete_user";
const QString EditGroup = "edit_group";
const QString EditLab = "edit_lab";
const QString EditSample = "edit_sample";
const QString EditSampleAdmin = "edit_sample_admin";
const QString EditSelf = "edit_self";
const QString EditUser = "edit_user";
const QString GenerateInvites = "generate_invites";
const QString GetGroupInfoList = "get_group_info_list";
const QString GetInviteInfoList = "get_invite_info_list";
const QString GetLabData = "get_lab_data";
const QString GetLabExtraFile = "get_lab_extra_file";
const QString GetLabInfoList = "get_lab_info_list";
const QString GetLatestAppVersion = "get_latest_app_version";
const QString GetSampleInfoList = "get_sample_info_list";
const QString GetSamplePreview = "get_sample_preview";
const QString GetSampleSource = "get_sample_source";
const QString GetSelfInfo = "get_self_info";
const QString GetUserAvatar = "get_user_avatar";
const QString GetUserInfo = "get_user_info";
const QString GetUserInfoAdmin = "get_user_info_admin";
const QString Log = "log";
const QString RecoverAccount = "recover_account";
const QString Register = "register";
const QString RequestRecoveryCode = "request_recovery_code";
const QString Subscribe = "subscribe";

}

#endif // TOPERATION_H
