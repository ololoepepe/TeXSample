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

#include "tnamespace.h"

#include <BDirTools>
#include <BTextTools>

#include <QByteArray>
#include <QBuffer>
#include <QFileInfo>
#include <QImage>
#include <QString>
#include <QUrl>
#include <QVariant>

B_DECLARE_TRANSLATE_FUNCTION

namespace Texsample
{

bool testAdminRemark(const QString &remark, QString *error, bool tr)
{
    if (remark.length() > Texsample::MaximumAdminRemarkLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testAvatar(const QImage &avatar, QString *error, bool tr)
{
    if (avatar.isNull())
        return bRet(error, tr ? translate("Texsample", "The image is invalid", "error") :
                                QString("The image is invalid"), false);
    if (avatar.height() > Texsample::MaximumAvatarExtent) {
        return bRet(error, tr ? translate("Texsample", "The image\'s height is too big", "error") :
                                QString("The image\'s height is too big"), false);
    }
    if (avatar.width() > Texsample::MaximumAvatarExtent) {
        return bRet(error, tr ? translate("Texsample", "The image\'s hwidth is too big", "error") :
                                QString("The image\'s hwidth is too big"), false);
    }
    QByteArray ba;
    QBuffer buff(&ba);
    buff.open(QBuffer::WriteOnly);
    if (!avatar.save(&buff, "png")) {
        return bRet(error, tr ? translate("Texsample", "Unable to test avatar", "error") :
                                QString("Unable to test avatar"), false);
    }
    if (ba.size() > Texsample::MaximumAvatarSize) {
        return bRet(error, tr ? translate("Texsample", "The image is too big", "error") :
                                QString("The image is too big"), false);
    }
    return bRet(error, QString(), true);
}

bool testAvatar(const QString &avatarFileName, QString *error, bool tr)
{
    return testAvatar(avatarFileName, 0, error, tr);
}

bool testAvatar(const QString &avatarFileName, QImage *image, QString *error, bool tr)
{
    if (avatarFileName.isEmpty()) {
        return bRet(error, tr ? translate("Texsample", "The file name is empty", "error") :
                                QString("The file name is empty"), false);
    }
    if (!QFileInfo(avatarFileName).isFile()) {
        return bRet(error, tr ? translate("Texsample", "The file does not exist", "error") :
                                QString("The file does not exist"), false);
    }
    bool ok = false;
    QByteArray data = BDirTools::readFile(avatarFileName, -1, &ok);
    if (!ok) {
        return bRet(error, tr ? translate("Texsample", "Failed to read file", "error") :
                                QString("Failed to read file"), false);
    }
    QImage img = QImage::fromData(data);
    return bRet(image, img, testAvatar(img, error, tr));
}

bool testCommand(const QString &command, QString *error, bool tr)
{
    if (command.isEmpty()) {
        return bRet(error, tr ? translate("Texsample", "The string is empty", "error") :
                                QString("The string is empty"), false);
    }
    if (command.length() > Texsample::MaximumCommandLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testEmail(const QString &email, QString *error, bool tr)
{
    if (email.isEmpty()) {
        return bRet(error, tr ? translate("Texsample", "The string is empty", "error") :
                                QString("The string is empty"), false);
    }
    if (email.length() > Texsample::MaximumEmailLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    if (!BTextTools::standardRegExp(BTextTools::EmailPattern).exactMatch(email)) {
        return bRet(error, tr ? translate("Texsample", "The string is not an e-mail", "error") :
                                QString("The string is not an e-mail"), false);
    }
    return bRet(error, QString(), true);
}

bool testFileDescription(const QString &description, QString *error, bool tr)
{
    if (description.length() > Texsample::MaximumFileDescriptionLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testGroupName(const QString &name, QString *error, bool tr)
{
    if (name.length() > Texsample::MaximumGroupNameLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testLabDescription(const QString &description, QString *error, bool tr)
{
    if (description.length() > Texsample::MaximumLabDescriptionLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testLabTitle(const QString &title, QString *error, bool tr)
{
    if (title.length() > Texsample::MaximumLabTitleLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testLogin(const QString &login, QString *error, bool tr)
{
    if (login.isEmpty()) {
        return bRet(error, tr ? translate("Texsample", "The string is empty", "error") :
                                QString("The string is empty"), false);
    }
    if (login.length() < Texsample::MinimumLoginLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too short", "error") :
                                QString("The string is too short"), false);
    }
    if (login.length() > Texsample::MaximumLoginLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testName(const QString &name, QString *error, bool tr)
{
    if (name.length() > Texsample::MaximumNameLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testOrganization(const QString &organization, QString *error, bool tr)
{
    if (organization.length() > Texsample::MaximumOrganizationLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testPassword(const QString &password, QString *error, bool tr)
{
    if (password.isEmpty()) {
        return bRet(error, tr ? translate("Texsample", "The string is empty", "error") :
                                QString("The string is empty"), false);
    }
    if (password.length() < Texsample::MinimumPasswordLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too short", "error")
                              : QString("The string is too short"), false);
    }
    if (password.length() > Texsample::MaximumPasswordLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testPassword(const QByteArray &password, QString *error, bool tr)
{
    if (password.size() != RawPasswordSize) {
        return bRet(error, tr ? translate("Texsample", "The password is not a correct SHA1 hash", "error") :
                                QString("The password is not a correct SHA1 hash"), false);
    }
    return bRet(error, QString(), true);
}

bool testPost(const QString &post, QString *error, bool tr)
{
    if (post.length() > Texsample::MaximumPostLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testRole(const QString &role, QString *error, bool tr)
{
    if (role.length() > Texsample::MaximumRoleLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testSampleDescription(const QString &description, QString *error, bool tr)
{
    if (description.length() > Texsample::MaximumSampleDescriptionLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testSampleTitle(const QString &title, QString *error, bool tr)
{
    if (title.length() > Texsample::MaximumSampleTitleLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    return bRet(error, QString(), true);
}

bool testUrl(const QString &url, QString *error, bool tr)
{
    if (url.length() > Texsample::MaximumUrlLength) {
        return bRet(error, tr ? translate("Texsample", "The string is too long", "error") :
                                QString("The string is too long"), false);
    }
    if (!QUrl::fromUserInput(url).isValid()) {
        return bRet(error, tr ? translate("Texsample", "The URL is invalid", "error") : QString("The URL is invalid"),
                    false);
    }
    return bRet(error, QString(), true);
}

}
