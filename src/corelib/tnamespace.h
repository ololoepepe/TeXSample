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

#ifndef TNAMESPACE_H
#define TNAMESPACE_H

class QByteArray;
class QImage;
class QString;

#include "tglobal.h"

#include <BeQt>

#include <QCryptographicHash>

namespace Texsample
{

enum ClientType
{
    UnknownClient = 0,
    CloudlabClient,
    TexCreator,
    TexsampleConsole
};

const quint16 MainPort = 9045;

const int MaximumAdminRemarkLength = 1000;
const int MaximumAvatarExtent = 2000;
const int MaximumAvatarSize = 2 * BeQt::Megabyte;
const int MaximumCommandLength = 40;
const int MaximumEmailLength = 60;
const int MaximumFileDescriptionLength = 1000;
const int MaximumGroupNameLength = 40;
const int MaximumLabDescriptionLength = 1000;
const int MaximumLabTitleLength = 100;
const int MaximumLoginLength = 20;
const int MaximumNameLength = 40;
const int MaximumOrganizationLength = 250;
const int MaximumPasswordLength = 20;
const int MaximumPatronymicLength = 40;
const int MaximumPostLength = 40;
const int MaximumUrlLength = 1000;
const int MaximumRoleLength = 40;
const int MaximumSampleDescriptionLength = 1000;
const int MaximumSampleTitleLength = 100;
const int MaximumSurameLength = 40;
const int MinimumLoginLength = 2;
const int MinimumPasswordLength = 8;
const QCryptographicHash::Algorithm PasswordEncryptionAlgorythm = QCryptographicHash::Sha1;
const int RawPasswordSize = 20;

T_CORE_EXPORT ClientType clientType();
T_CORE_EXPORT QString clientTypeToString(ClientType t);
T_CORE_EXPORT QByteArray encryptPassword(const QString &password);
T_CORE_EXPORT bool testAdminRemark(const QString &remark, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QImage &avatar, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QString &avatarFileName, QImage *image, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QString &avatarFileName, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testCommand(const QString &command, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testEmail(const QString &email, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testFileDescription(const QString &description, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testGroupName(const QString &name, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testLabDescription(const QString &description, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testLabTitle(const QString &title, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testLogin(const QString &login, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testName(const QString &name, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testOrganization(const QString &organization, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testPassword(const QString &password, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testPassword(const QByteArray &password, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testPatronymic(const QString &name, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testPost(const QString &post, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testRole(const QString &role, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testSampleDescription(const QString &description, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testSampleTitle(const QString &title, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testSurname(const QString &name, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testUrl(const QString &url, QString *error = 0, bool translate = true);

}

#endif // TNAMESPACE_H
