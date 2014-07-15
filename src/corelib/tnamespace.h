#ifndef TNAMESPACE_H
#define TNAMESPACE_H

class QImage;
class QString;

#include "tglobal.h"

#include <BeQt>

namespace Texsample
{

const quint16 MainPort = 9044; //TODO: Change to 9045 or something else

const int MaximumAdminRemarkLength = 1000;
const int MaximumAvatarExtent = 2000;
const int MaximumAvatarSize = 2 * BeQt::Megabyte;
const int MaximumEmailLength = 60;
const int MaximumFileDescriptionLength = 1000;
const int MaximumGroupNameLength = 40;
const int MaximumLabDescriptionLength = 1000;
const int MaximumLabTitleLength = 100;
const int MaximumLoginLength = 20;
const int MaximumNameLength = 20;
const int MaximumOrganizationLength = 250;
const int MaximumPasswordLength = 20;
const int MaximumPostLength = 40;
const int MaximumUrlLength = 1000;
const int MaximumRoleLength = 40;
const int MaximumSampleDescriptionLength = 1000;
const int MaximumSampleTitleLength = 100;
const int MinimumLoginLength = 2;
const int MinimumPasswordLength = 8;

T_CORE_EXPORT bool testAdminRemark(const QString &remark, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QImage &avatar, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QString &avatarFileName, QImage *image, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testAvatar(const QString &avatarFileName, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testEmail(const QString &email, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testFileDescription(const QString &description, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testGroupName(const QString &name, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testLabDescription(const QString &description, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testLabTitle(const QString &title, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testLogin(const QString &login, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testName(const QString &name, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testOrganization(const QString &organization, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testPassword(const QString &password, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testPost(const QString &post, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testRole(const QString &role, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testSampleDescription(const QString &description, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testSampleTitle(const QString &title, QString *error = 0, bool translate = true);
T_CORE_EXPORT bool testUrl(const QString &url, QString *error = 0, bool translate = true);

}

#endif // TNAMESPACE_H
