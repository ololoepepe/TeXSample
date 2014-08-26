/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleNetworkWidgets module
** of the TeXSample library.
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

#ifndef TUSERINFOWIDGET_P_H
#define TUSERINFOWIDGET_P_H

class TAbstractCache;
class TGroupInfoList;
class TIdList;
class TListWidget;
class TNetworkClient;
class TServiceList;
class TServiceWidget;
class TUserModel;

class BEditGroup;
class BInputField;
class BPasswordGroup;
class BPasswordWidget;

class QCheckBox;
class QComboBox;
class QFormLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QToolButton;
class QVBoxLayout;

#include "tuserinfowidget.h"

#include <TeXSampleCore/TService>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QImage>
#include <QMap>
#include <QString>
#include <QWidget>

/*============================================================================
================================ TUserInfoWidgetPrivate ======================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TUserInfoWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TUserInfoWidget)
public:
    enum EditGroupMode
    {
        NormalMode = 1,
        OptionalMode,
        SeparateMode
    };
public:
    static const QString DateTimeFormat;
public:
    const TUserInfoWidget::Mode Mode;
public:
    QImage avatar;
    QString avatarFileName;
    QPushButton *btnChangeEmail;
    QPushButton *btnChangePassword;
    QCheckBox *cboxActive;
    QCheckBox *cboxChangeEmail;
    QCheckBox *cboxChangePassword;
    TAbstractCache *cache;
    TNetworkClient *client;
    QComboBox *cmboxAccessLevel;
    BEditGroup *edtgrpEmail;
    quint64 id;
    BInputField *inputEmail1;
    BInputField *inputEmail2;
    BInputField *inputInvite;
    BInputField *inputLogin;
    BInputField *inputPwd1;
    BInputField *inputPwd2;
    BInputField *inputPwdOld;
    QLabel *lblEmailOld;
    QLabel *lblLastModificationDateTime;
    QLabel *lblRegistrationDateTime;
    QLineEdit *ledtEmail1;
    QLineEdit *ledtEmail2;
    QLineEdit *ledtInvite;
    QLineEdit *ledtLogin;
    QLineEdit *ledtName;
    QLineEdit *ledtPatronymic;
    QLineEdit *ledtSurname;
    TListWidget *lstwgtGroups;
    TUserModel *model;
    QMap<QString, bool> occupiedEmails;
    QMap<QString, bool> occupiedLogins;
    BPasswordGroup *pwdgrp;
    BPasswordWidget *pwdwgt1;
    BPasswordWidget *pwdwgt2;
    BPasswordWidget *pwdwgtOld;
    TServiceWidget *srvwgt;
    QToolButton *tbtnAvatar;
    QToolButton *tbtnCheckEmail;
    QToolButton *tbtnCheckLogin;
    QToolButton *tbtnClearAvatar;
    bool valid;
public:
    explicit TUserInfoWidgetPrivate(TUserInfoWidget *q, TUserInfoWidget::Mode m);
    ~TUserInfoWidgetPrivate();
public:
    void createAccessLevelField(QFormLayout *flt, bool readOnly = false);
    void createActiveField(QFormLayout *flt, bool readOnly = false);
    void createAvatarButton(QHBoxLayout *hlt, bool readOnly = false);
    void createEmailGroup(QFormLayout *flt, EditGroupMode mode = NormalMode);
    void createGroupsSection(QVBoxLayout *vlt, bool readOnly = false);
    void createInviteField(QFormLayout *flt);
    void createLastModificationDateTimeField(QFormLayout *flt);
    void createLoginFiled(QFormLayout *flt, bool readOnly = false);
    void createNameFields(QFormLayout *flt, bool readOnly = false);
    void createPasswordGroup(QFormLayout *flt, EditGroupMode mode = NormalMode);
    void createRegistrationDateTimeField(QFormLayout *flt);
    void createServicesSection(QHBoxLayout *hlt, bool readOnly = false);
    TGroupInfoList groupInfos() const;
    TIdList groups() const;
    void init();
    void setGroups(const TGroupInfoList &list);
public Q_SLOTS:
    void changeEmail();
    void changePassword();
    void checkChangeEmailInputs();
    void checkChangePasswordInputs();
    void checkEmail();
    void checkInputs();
    void checkLogin();
    void clientAnonymousValidityChanged(bool valid);
    void clientAuthorizedChanged(bool);
    void resetAvatar(const QImage &image = QImage());
    void tbtnAvatarClicked();
private:
    Q_DISABLE_COPY(TUserInfoWidgetPrivate)
};

#endif // TUSERINFOWIDGET_P_H
