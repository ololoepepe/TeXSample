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

#include "tuserinfowidget.h"
#include "tuserinfowidget_p.h"

#include "tlistwidget.h"

#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TAddUserRequestData>
#include <TeXSampleCore/TChangeEmailRequestData>
#include <TeXSampleCore/TChangePasswordRequestData>
#include <TeXSampleCore/TCheckEmailAvailabilityReplyData>
#include <TeXSampleCore/TCheckEmailAvailabilityRequestData>
#include <TeXSampleCore/TCheckLoginAvailabilityReplyData>
#include <TeXSampleCore/TCheckLoginAvailabilityRequestData>
#include <TeXSampleCore/TEditSelfRequestData>
#include <TeXSampleCore/TEditUserRequestData>
#include <TeXSampleCore/TeXSample>
#include <TeXSampleCore/TGetUserAvatarReplyData>
#include <TeXSampleCore/TGetUserAvatarRequestData>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TIdList>
#include <TeXSampleCore/TMessage>
#include <TeXSampleCore/TOperation>
#include <TeXSampleCore/TRegisterRequestData>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>
#include <TeXSampleCore/TUserIdentifier>
#include <TeXSampleCore/TUserInfo>
#include <TeXSampleCore/TUserModel>
#include <TeXSampleNetwork/TNetworkClient>

#include <BApplication>
#include <BBaseObject>
#include <BDialog>
#include <BEditGroup>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BGuiTools>
#include <BInputField>
#include <BPasswordGroup>
#include <BPasswordWidget>
#include <BTextTools>

#include <QCheckBox>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFont>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMap>
#include <QMessageBox>
#include <QMetaObject>
#include <QPixmap>
#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QScrollArea>
#include <QSize>
#include <QStringList>
#include <QToolButton>
#include <QToolTip>
#include <QValidator>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

/*============================================================================
================================ TUserInfoWidgetPrivate ======================
============================================================================*/

/*============================== Static public constants ===================*/

const QString TUserInfoWidgetPrivate::DateTimeFormat = "dd MMMM yyyy hh:mm";

/*============================== Public constructors =======================*/

TUserInfoWidgetPrivate::TUserInfoWidgetPrivate(TUserInfoWidget *q, TUserInfoWidget::Mode m) :
    BBaseObjectPrivate(q), Mode(m)
{
    //
}

TUserInfoWidgetPrivate::~TUserInfoWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserInfoWidgetPrivate::createAccessLevelField(QFormLayout *flt, bool readOnly)
{
    cmboxAccessLevel = new QComboBox;
      cmboxAccessLevel->setEnabled(!readOnly);
      foreach (const TAccessLevel &lvl, TAccessLevel::allAccessLevels())
          cmboxAccessLevel->addItem(lvl.toString(), int(lvl));
      if (cmboxAccessLevel->count())
        cmboxAccessLevel->setCurrentIndex(0);
    flt->addRow(tr("Access level:", "lbl text"), cmboxAccessLevel);
}

void TUserInfoWidgetPrivate::createActiveField(QFormLayout *flt, bool readOnly)
{
    cboxActive = new QCheckBox;
      cboxActive->setEnabled(!readOnly);
    flt->addRow(tr("Active:", "lbl text"), cboxActive);
}

void TUserInfoWidgetPrivate::createAvatarButton(QHBoxLayout *hlt, bool readOnly)
{
    QGroupBox *gbox = new QGroupBox(tr("Avatar", "gbox title"));
      QHBoxLayout *vlt = new QHBoxLayout(gbox);
        tbtnAvatar = new QToolButton;
          tbtnAvatar->setIconSize(QSize(128, 128));
          if (!readOnly) {
              tbtnAvatar->setToolTip(tr("Click to select a new picture", "tbtn toolTip"));
              QVBoxLayout *vltww = new QVBoxLayout(tbtnAvatar);
                vltww->addStretch();
                tbtnClearAvatar = new QToolButton;
                  tbtnClearAvatar->setIconSize(QSize(16, 16));
                  tbtnClearAvatar->setIcon(BApplication::icon("editdelete"));
                  tbtnClearAvatar->setToolTip(tr("Clear avatar", "tbtn toolTip"));
                  connect(tbtnClearAvatar, SIGNAL(clicked()), this, SLOT(resetAvatar()));
                vltww->addWidget(tbtnClearAvatar);
          }
          connect(tbtnAvatar, SIGNAL(clicked()), this, SLOT(tbtnAvatarClicked()));
          resetAvatar();
          editAvatar = false;
        vlt->addWidget(tbtnAvatar);
    hlt->addWidget(gbox);

}

void TUserInfoWidgetPrivate::createEmailGroup(QFormLayout *flt, EditGroupMode mode)
{
    edtgrpEmail = new BEditGroup(this);
    if (OptionalMode == mode || SeparateMode == mode) {
        lblEmailOld = new QLabel;
        flt->addRow(tr("E-mail:", "lbl text"), lblEmailOld);
    }
    if (OptionalMode == mode) {
        cboxChangeEmail = new QCheckBox;
          connect(cboxChangeEmail, SIGNAL(toggled(bool)), this, SLOT(checkInputs()));
        flt->addRow(tr("Change e-mail:", "lbl text"), cboxChangeEmail);
    }
    ledtEmail1 = new QLineEdit;
      ledtEmail1->setMaxLength(Texsample::MaximumEmailLength);
      ledtEmail1->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern), this));
      connect(ledtEmail1, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
      inputEmail1 = new BInputField;
      inputEmail1->addWidget(ledtEmail1);
      edtgrpEmail->addEdit(ledtEmail1);
      QHBoxLayout *hlt = new QHBoxLayout;
      hlt->addWidget(inputEmail1);
      tbtnCheckEmail = new QToolButton;
        QSize sz = QSize(ledtEmail1->sizeHint().height(), ledtEmail1->sizeHint().height());
        tbtnCheckEmail->setIconSize(sz - (tbtnCheckEmail->sizeHint() - tbtnCheckEmail->iconSize()));
        tbtnCheckEmail->setToolTip(tr("Check e-mail", "tbtn toolTip"));
        tbtnCheckEmail->setIcon(BApplication::icon("network"));
        tbtnCheckEmail->setFixedSize(sz);
        connect(tbtnCheckEmail, SIGNAL(clicked()), this, SLOT(checkEmail()));
      hlt->addWidget(tbtnCheckEmail);
    flt->addRow(tr("E-mail:", "lbl text"), hlt);
    ledtEmail2 = new QLineEdit;
      ledtEmail1->setMaxLength(Texsample::MaximumEmailLength);
      ledtEmail2->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern), this));
      connect(ledtEmail2, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
      inputEmail2 = new BInputField;
      inputEmail2->addWidget(ledtEmail2);
      edtgrpEmail->addEdit(ledtEmail2);
      connect(edtgrpEmail, SIGNAL(textsMatchAndAcceptableChanged(bool)), inputEmail2, SLOT(setValid(bool)));
    flt->addRow(tr("E-mail confirmation:", "lbl text"), inputEmail2);
    if (SeparateMode == mode) {
        btnChangeEmail = new QPushButton(tr("Change e-mail", "btn text"));
          connect(btnChangeEmail, SIGNAL(clicked()), this, SLOT(changeEmail()));
        flt->addRow("", btnChangeEmail);
        connect(edtgrpEmail, SIGNAL(textsMatchChanged(bool)), this, SLOT(checkChangeEmailInputs()));
    } else {
        connect(edtgrpEmail, SIGNAL(textsMatchChanged(bool)), this, SLOT(checkInputs()));
    }
}

void TUserInfoWidgetPrivate::createGroupsSection(QVBoxLayout *vlt, bool readOnly)
{
    QGroupBox *gbox = new QGroupBox(tr("Groups", "gbox title"));
      QHBoxLayout *hlt = new QHBoxLayout(gbox);
        lstwgtGroups = new TListWidget;
          lstwgtGroups->setReadOnly(true);
          lstwgtGroups->setButtonsVisible(!readOnly);
        hlt->addWidget(lstwgtGroups);
    vlt->addWidget(gbox);
}

void TUserInfoWidgetPrivate::createInviteField(QFormLayout *flt)
{
    inputInvite = new BInputField;
      ledtInvite = new QLineEdit;
        ledtInvite->setFont(BGuiTools::createMonospaceFont());
        ledtInvite->setInputMask("HHHHHHHH-HHHH-HHHH-HHHH-HHHHHHHHHHHH;_");
        connect(ledtInvite, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
      inputInvite->addWidget(ledtInvite);
    flt->addRow(tr("Invite:", "lbl text"), inputInvite);
}

void TUserInfoWidgetPrivate::createLastModificationDateTimeField(QFormLayout *flt)
{
    lblLastModificationDateTime = new QLabel;
    flt->addRow(tr("Last modified:", "lbl text"), lblLastModificationDateTime);
}

void TUserInfoWidgetPrivate::createLoginFiled(QFormLayout *flt, bool readOnly)
{
    QRegExp rx(".{" + QString::number(Texsample::MinimumLoginLength) + ","
               + QString::number(Texsample::MaximumLoginLength) + "}");
    ledtLogin = new QLineEdit;
      ledtLogin->setValidator(new QRegExpValidator(rx, this));
      ledtLogin->setMaxLength(Texsample::MaximumLoginLength);
      ledtLogin->setReadOnly(readOnly);
      connect(ledtLogin, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
      inputLogin = new BInputField;
      inputLogin->addWidget(ledtLogin);
      QHBoxLayout *hlt = new QHBoxLayout;
      hlt->addWidget(inputLogin);
      if (!readOnly) {
          tbtnCheckLogin = new QToolButton;
            QSize sz = QSize(ledtLogin->sizeHint().height(), ledtLogin->sizeHint().height());
            tbtnCheckLogin->setIconSize(sz - (tbtnCheckLogin->sizeHint() - tbtnCheckLogin->iconSize()));
            tbtnCheckLogin->setToolTip(tr("Check login", "tbtn toolTip"));
            tbtnCheckLogin->setIcon(BApplication::icon("network"));
            tbtnCheckLogin->setFixedSize(sz);
            connect(tbtnCheckLogin, SIGNAL(clicked()), this, SLOT(checkLogin()));
          hlt->addWidget(tbtnCheckLogin);
      }
    flt->addRow(tr("Login:", "lbl text"), hlt);
}

void TUserInfoWidgetPrivate::createNameFields(QFormLayout *flt, bool readOnly)
{
    ledtName = new QLineEdit;
      ledtName->setMaxLength(Texsample::MaximumNameLength);
      ledtName->setReadOnly(readOnly);
    flt->addRow(tr("Name:", "lbl text"), ledtName);
    ledtPatronymic = new QLineEdit;
      ledtPatronymic->setMaxLength(Texsample::MaximumNameLength);
      ledtPatronymic->setReadOnly(readOnly);
    flt->addRow(tr("Patronymic:", "lbl text"), ledtPatronymic);
    ledtSurname = new QLineEdit;
      ledtSurname->setMaxLength(Texsample::MaximumNameLength);
      ledtSurname->setReadOnly(readOnly);
    flt->addRow(tr("Surname:", "lbl text"), ledtSurname);
}

void TUserInfoWidgetPrivate::createPasswordGroup(QFormLayout *flt, EditGroupMode mode)
{
    QRegExp rx(".{" + QString::number(Texsample::MinimumPasswordLength) + ","
               + QString::number(Texsample::MaximumPasswordLength) + "}");
    pwdgrp = new BPasswordGroup(this);
    if (OptionalMode == mode) {
        cboxChangePassword = new QCheckBox;
          connect(cboxChangePassword, SIGNAL(toggled(bool)), this, SLOT(checkInputs()));
        flt->addRow(tr("Change password:", "lbl text"), cboxChangePassword);
    }
    if (SeparateMode == mode) {
        inputPwdOld = new BInputField;
          pwdwgtOld = new BPasswordWidget;
            pwdwgtOld->setValidator(new QRegExpValidator(rx, this));
            connect(pwdwgtOld, SIGNAL(passwordChanged()), this, SLOT(checkChangeEmailInputs()));
            connect(pwdwgtOld, SIGNAL(passwordChanged()), this, SLOT(checkChangePasswordInputs()));
          inputPwdOld->addWidget(pwdwgtOld);
        flt->addRow(tr("Old password:", "lbl text"), inputPwdOld);
    }
    pwdwgt1 = new BPasswordWidget;
      pwdwgt1->setValidator(new QRegExpValidator(rx, this));
      pwdwgt1->setSavePasswordVisible(false);
      pwdwgt1->setShowPasswordVisible(false);
      pwdwgt1->setGeneratePasswordVisible(true);
      connect(pwdwgt1, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
      inputPwd1 = new BInputField;
      inputPwd1->addWidget(pwdwgt1);
      pwdgrp->addPasswordWidget(pwdwgt1);
    flt->addRow(tr("Password:", "lbl text"), inputPwd1);
    pwdwgt2 = new BPasswordWidget;
      pwdwgt2->setValidator(new QRegExpValidator(rx, this));
      pwdwgt2->setSavePasswordVisible(false);
      connect(pwdwgt1, SIGNAL(showPasswordChanged(bool)), pwdwgt2, SLOT(setShowPassword(bool)));
      connect(pwdwgt2, SIGNAL(showPasswordChanged(bool)), pwdwgt1, SLOT(setShowPassword(bool)));
      connect(pwdwgt2, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
      inputPwd2 = new BInputField;
      inputPwd2->addWidget(pwdwgt2);
      pwdgrp->addPasswordWidget(pwdwgt2);
      connect(pwdgrp, SIGNAL(passwordsMatchAndAcceptableChanged(bool)), inputPwd2, SLOT(setValid(bool)));
    flt->addRow(tr("Password confirmation:", "lbl text"), inputPwd2);
    if (SeparateMode == mode) {
        btnChangePassword = new QPushButton(tr("Change password", "btn text"));
          connect(btnChangePassword, SIGNAL(clicked()), this, SLOT(changePassword()));
        flt->addRow("", btnChangePassword);
        connect(pwdgrp, SIGNAL(passwordsMatchChanged(bool)), this, SLOT(checkChangePasswordInputs()));
    } else {
        connect(pwdgrp, SIGNAL(passwordsMatchChanged(bool)), this, SLOT(checkInputs()));
    }
}

void TUserInfoWidgetPrivate::createRegistrationDateTimeField(QFormLayout *flt)
{
    lblRegistrationDateTime = new QLabel;
    flt->addRow(tr("Registration date:", "lbl text"), lblRegistrationDateTime);
}

void TUserInfoWidgetPrivate::createServicesSection(QHBoxLayout *hlt, bool readOnly)
{
    QGroupBox *gbox = new QGroupBox(tr("Services", "gbox title"));
      QFormLayout *flt = new QFormLayout(gbox);
      foreach (const TService &s, TServiceList::allServices()) {
          QCheckBox *cbox = new QCheckBox;
            cbox->setEnabled(!readOnly);
          flt->addRow(tr("Access to", "lbl text") + " " + s.toString() + ":", cbox);
          cboxServiceMap.insert(s, cbox);
      }
    hlt->addWidget(gbox);
}

TIdList TUserInfoWidgetPrivate::groups() const
{
    TIdList list;
    if (!lstwgtGroups)
        return list;
    foreach (int i, bRangeD(0, lstwgtGroups->itemCount() - 1))
        list << lstwgtGroups->itemData(i).toULongLong();
    return list;
}

void TUserInfoWidgetPrivate::init()
{
    client = 0;
    model = 0;
    editAvatar = false;
    containsAvatar = false;
    valid = false;
    cboxActive = 0;
    cboxChangeEmail = 0;
    cboxChangePassword = 0;
    cmboxAccessLevel = 0;
    edtgrpEmail = 0;
    inputEmail1 = 0;
    inputEmail2 = 0;
    inputInvite = 0;
    inputLogin = 0;
    inputPwd1 = 0;
    inputPwd2 = 0;
    inputPwdOld = 0;
    lblLastModificationDateTime = 0;
    lblRegistrationDateTime = 0;
    ledtEmail1 = 0;
    ledtEmail2 = 0;
    lblEmailOld = 0;
    ledtInvite = 0;
    ledtLogin = 0;
    ledtName = 0;
    ledtPatronymic = 0;
    ledtSurname = 0;
    lstwgtGroups = 0;
    pwdgrp = 0;
    pwdwgt1 = 0;
    pwdwgt2 = 0;
    pwdwgtOld = 0;
    tbtnAvatar = 0;
    tbtnCheckEmail = 0;
    tbtnCheckLogin = 0;
    tbtnClearAvatar = 0;
    btnChangeEmail = 0;
    btnChangePassword = 0;
    QHBoxLayout *hlt = new QHBoxLayout(q_func());
    switch (Mode) {
    case TUserInfoWidget::AddMode: {
        QFormLayout *flt = new QFormLayout;
          createLoginFiled(flt);
          createEmailGroup(flt);
          createPasswordGroup(flt);
          createAccessLevelField(flt);
          createNameFields(flt);
        hlt->addLayout(flt);
        break;
    }
    case TUserInfoWidget::EditMode: {
        QFormLayout *flt = new QFormLayout;
          createLoginFiled(flt, true);
          createEmailGroup(flt, OptionalMode);
          createPasswordGroup(flt, OptionalMode);
          createAccessLevelField(flt);
          createActiveField(flt);
          createNameFields(flt);
          createRegistrationDateTimeField(flt);
          createLastModificationDateTimeField(flt);
        hlt->addLayout(flt);
        break;
    }
    case TUserInfoWidget::EditSelfMode: {
        QVBoxLayout *vlt = new QVBoxLayout;
          QFormLayout *flt = new QFormLayout;
            createLoginFiled(flt, true);
            createAccessLevelField(flt, true);
            createActiveField(flt, true);
            createNameFields(flt);
          vlt->addLayout(flt);
          QGroupBox *gbox = new QGroupBox(tr("Security", "gbox title"));
            flt = new QFormLayout(gbox);
              createPasswordGroup(flt, SeparateMode);
              createEmailGroup(flt, SeparateMode);
          flt = new QFormLayout;
            createRegistrationDateTimeField(flt);
            createLastModificationDateTimeField(flt);
          vlt->addLayout(flt);
        hlt->addLayout(vlt);
        break;
    }
    case TUserInfoWidget::RegisterMode: {
        QFormLayout *flt = new QFormLayout;
          createInviteField(flt);
          createLoginFiled(flt);
          createEmailGroup(flt);
          createPasswordGroup(flt);
          createNameFields(flt);
        hlt->addLayout(flt);
        break;
    }
    case TUserInfoWidget::ShowMode: {
        QFormLayout *flt = new QFormLayout;
          createLoginFiled(flt, true);
          createAccessLevelField(flt, true);
          createActiveField(flt, true);
          createNameFields(flt, true);
          createRegistrationDateTimeField(flt);
        hlt->addLayout(flt);
        break;
    }
    default: {
        break;
    }
    }
    hlt->addWidget(BGuiTools::createFrame(QFrame::VLine));
    QVBoxLayout *vlt = new QVBoxLayout;
      QHBoxLayout *hltww = new QHBoxLayout;
        createAvatarButton(hltww, TUserInfoWidget::ShowMode == Mode);
        if (TUserInfoWidget::RegisterMode != Mode)
            createServicesSection(hltww, TUserInfoWidget::EditSelfMode == Mode || TUserInfoWidget::ShowMode == Mode);
      vlt->addLayout(hltww);
      if (TUserInfoWidget::RegisterMode != Mode)
        createGroupsSection(vlt, TUserInfoWidget::EditSelfMode == Mode || TUserInfoWidget::ShowMode == Mode);
    hlt->addLayout(vlt);
    //
    checkInputs();
    checkChangeEmailInputs();
    checkChangePasswordInputs();
}

TServiceList TUserInfoWidgetPrivate::services() const
{
    TServiceList list;
    if (cboxServiceMap.isEmpty())
        return list;
    foreach (const TService &service, TServiceList::allServices()) {
        if (cboxServiceMap.value(service)->isChecked())
            list << service;
    }
    return list;
}

/*============================== Public slots ==============================*/

void TUserInfoWidgetPrivate::changeEmail()
{
    if (!client)
        return;
    QString email = ledtEmail1->text();
    TChangeEmailRequestData data;
    data.setEmail(email);
    data.setPassword(pwdwgtOld->openPassword());
    TReply r = client->performOperation(TOperation::ChangeEmail, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Changing e-mail failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to change e-mail. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    } else {
        occupiedEmails.insert(email, true);
        checkInputs();
    }
}

void TUserInfoWidgetPrivate::changePassword()
{
    if (!client)
        return;
    TChangePasswordRequestData data;
    data.setOldPassword(Texsample::encryptPassword(pwdwgtOld->openPassword()));
    data.setNewPassword(Texsample::encryptPassword(pwdwgt1->openPassword()));
    TReply r = client->performOperation(TOperation::ChangePassword, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Changing password failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to change password. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
}

void TUserInfoWidgetPrivate::checkChangeEmailInputs()
{
    if (!btnChangeEmail)
        return;
    btnChangeEmail->setEnabled(client && client->isAuthorized() && pwdwgtOld->hasAcceptableInput()
                               && edtgrpEmail->textsMatchAndAcceptable());
}

void TUserInfoWidgetPrivate::checkChangePasswordInputs()
{
    if (!btnChangePassword)
        return;
    inputPwdOld->setValid(pwdwgtOld->hasAcceptableInput());
    btnChangePassword->setEnabled(client && client->isAuthorized() && pwdwgtOld->hasAcceptableInput()
                                  && pwdgrp->passwordsMatchAndAcceptable());
}

void TUserInfoWidgetPrivate::checkEmail()
{
    if (!client)
        return;
    QString email = ledtEmail1->text();
    TCheckEmailAvailabilityRequestData data;
    data.setEmail(email);
    TReply r = client->performAnonymousOperation(TOperation::CheckEmailAvailability, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Checking e-mail failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to check e-mail. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    QPoint p = inputEmail1->mapToGlobal(tbtnCheckEmail->pos()) + QPoint(tbtnCheckEmail->width(), 0);
    if (r.data().value<TCheckEmailAvailabilityReplyData>().available()) {
        occupiedEmails.remove(email);
        QToolTip::showText(p, tr("The e-mail is free", "toolTip"), tbtnCheckEmail);
    } else {
        occupiedEmails.insert(email, true);
        QToolTip::showText(p, tr("The e-mail is occupied", "toolTip"), tbtnCheckEmail);
    }
    checkInputs();
}

void TUserInfoWidgetPrivate::checkInputs()
{
    bool idValid = TUserInfoWidget::AddMode == Mode || TUserInfoWidget::RegisterMode == Mode || id;
    bool inviteValid = !ledtInvite || ledtInvite->hasAcceptableInput();
    bool loginValid = !ledtLogin || (ledtLogin->hasAcceptableInput() && !occupiedLogins.contains(ledtLogin->text()));
    bool emailValid = !edtgrpEmail || (edtgrpEmail->textsMatchAndAcceptable()
                                       && !occupiedEmails.contains(ledtEmail1->text()));
    bool passwordValid = !pwdgrp || pwdgrp->passwordsMatchAndAcceptable();
    if (cboxChangeEmail) {
        inputEmail1->setEnabled(cboxChangeEmail->isChecked());
        inputEmail2->setEnabled(cboxChangeEmail->isChecked());
    }
    if (cboxChangePassword) {
        inputPwd1->setEnabled(cboxChangePassword->isChecked());
        inputPwd2->setEnabled(cboxChangePassword->isChecked());
    }
    if (inputInvite)
        inputInvite->setValid(inviteValid);
    if (inputLogin)
        inputLogin->setValid(loginValid);
    if (tbtnCheckLogin)
        tbtnCheckLogin->setEnabled(client && client->isValid(true) && ledtLogin->hasAcceptableInput());
    if (inputEmail1)
        inputEmail1->setValid(ledtEmail1->hasAcceptableInput());
    if (tbtnCheckEmail) {
        tbtnCheckEmail->setEnabled((!cboxChangeEmail || cboxChangeEmail->isChecked())
                                   && client && client->isValid(true) && ledtEmail1->hasAcceptableInput());
    }
    if (inputPwd1)
        inputPwd1->setValid(pwdwgt1->hasAcceptableInput());
    bool v = idValid && inviteValid && loginValid && ((cboxChangeEmail && !cboxChangeEmail->isChecked()) || emailValid)
            && ((cboxChangePassword && !cboxChangePassword->isChecked()) || passwordValid);
    if (v != valid) {
        valid = v;
        QMetaObject::invokeMethod(q_func(), "inputValidityChanged", Q_ARG(bool, v));
    }
}

void TUserInfoWidgetPrivate::checkLogin()
{
    if (!client)
        return;
    QString login = ledtLogin->text();
    TCheckLoginAvailabilityRequestData data;
    data.setLogin(login);
    TReply r = client->performAnonymousOperation(TOperation::CheckLoginAvailability, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Checking login failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to check login. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    QPoint p = inputLogin->mapToGlobal(tbtnCheckLogin->pos()) + QPoint(tbtnCheckLogin->width(), 0);
    if (r.data().value<TCheckLoginAvailabilityReplyData>().available()) {
        occupiedLogins.remove(login);
        QToolTip::showText(p, tr("The login is free", "toolTip"), tbtnCheckLogin);
    } else {
        occupiedLogins.insert(login, true);
        QToolTip::showText(p, tr("The login is occupied", "toolTip"), tbtnCheckLogin);
    }
    checkInputs();
}

void TUserInfoWidgetPrivate::clientAnonymousValidityChanged(bool valid)
{
    if (tbtnCheckLogin)
        tbtnCheckLogin->setEnabled(client && valid && ledtLogin->hasAcceptableInput());
    if (tbtnCheckEmail)
        tbtnCheckEmail->setEnabled(client && valid && ledtEmail1->hasAcceptableInput());
}

void TUserInfoWidgetPrivate::clientAuthorizedChanged(bool authorized)
{
    checkChangeEmailInputs();
    checkChangePasswordInputs();
    if (TUserInfoWidget::ShowMode == Mode && !containsAvatar)
        tbtnAvatar->setEnabled(client && authorized);
    if (cmboxAccessLevel && TUserInfoWidget::ShowMode != Mode) {
        foreach (const TAccessLevel &lvl, TAccessLevel::allAccessLevels()) {
            int ind = cmboxAccessLevel->findData(int(lvl));
            bool enabled = client && client->isAuthorized() && client->userInfo().accessLevel() >= lvl;
            BGuiTools::setItemEnabled(cmboxAccessLevel, ind, enabled);
            if (!enabled && cmboxAccessLevel->currentIndex() == ind && ind > 0)
                cmboxAccessLevel->setCurrentIndex(ind - 1);
        }
    }
    if (lstwgtGroups) {
        lstwgtGroups->clear();
        QList<TListWidget::Item> list;
        if (client && client->isAuthorized()) {
            foreach (const TGroupInfo &group, client->userInfo().availableGroups()) {
                TListWidget::Item item;
                item.text = group.name();
                item.data = group.id();
                list << item;
            }
        }
        lstwgtGroups->setAvailableItems(list);
    }
    if (!cboxServiceMap.isEmpty() && (TUserInfoWidget::AddMode == Mode || TUserInfoWidget::EditMode == Mode)) {
        foreach (const TService &service, TServiceList::allServices()) {
            cboxServiceMap.value(service)->setEnabled(client && client->isAuthorized()
                                                      && client->userInfo().availableServices().contains(service));
        }
    }
}

void TUserInfoWidgetPrivate::resetAvatar(const QImage &image)
{
    if (!tbtnAvatar)
        return;
    avatar = image;
    if (!avatar.isNull()) {
        tbtnAvatar->setIcon(QIcon(QPixmap::fromImage(avatar)));
        if (tbtnClearAvatar)
            tbtnClearAvatar->setEnabled(true);
    } else {
        tbtnAvatar->setIcon(BApplication::icon("user"));
        if (tbtnClearAvatar)
            tbtnClearAvatar->setEnabled(false);
    }
    if (TUserInfoWidget::ShowMode == Mode) {
        if (containsAvatar) {
            tbtnAvatar->setToolTip(!avatar.isNull() ? tr("Click to see the picture in full size", "tbtn toolTip") :
                                                      QString());
            tbtnAvatar->setEnabled(!avatar.isNull());
        } else {
            tbtnAvatar->setToolTip(!avatar.isNull() ? tr("Click to see the avatar", "tbtn toolTip") : QString());
            tbtnAvatar->setEnabled(client);
        }
    }
    editAvatar = true;
}

void TUserInfoWidgetPrivate::tbtnAvatarClicked()
{
    if (TUserInfoWidget::ShowMode == Mode) {
        if (!containsAvatar) {
            if (!client)
                return;
            TGetUserAvatarRequestData data;
            data.setIdentifier(id);
            TReply r = client->performOperation(TOperation::GetUserAvatar, data, q_func());
            if (!r) {
                QMessageBox msg(q_func());
                msg.setWindowTitle(tr("Failed to get avatar", "msgbox windowTitle"));
                msg.setIcon(QMessageBox::Critical);
                msg.setText(tr("Failed to get user avatar from server. The following error occured:", "msgbox text"));
                msg.setInformativeText(r.messageText());
                msg.setStandardButtons(QMessageBox::Ok);
                msg.exec();
                return;
            }
            avatar = r.data().value<TGetUserAvatarReplyData>().avatar();
            containsAvatar = true;
            if (model)
                model->updateUserAvatar(id, avatar);
        }
        BDialog dlg(q_func());
          dlg.setWindowTitle(tr("Avatar:", "dlg windowTitle") + " " + ledtLogin->text());
          dlg.addButton(QDialogButtonBox::Close, SLOT(close()));
          QScrollArea *sa = new QScrollArea;
            QLabel *lbl = new QLabel;
              lbl->setPixmap(QPixmap::fromImage(avatar));
              lbl->setToolTip(QString::number(avatar.width()) + "x" + QString::number(avatar.height()));
            sa->setWidget(lbl);
          dlg.setWidget(sa);
          dlg.setMinimumSize(600, 600);
          dlg.resize(600, 600);
        dlg.exec();
    } else {
        QString caption = tr("Select file", "fdlg caption");
        QString filter = tr("Images", "fdlg filter") + " (*.jpg *.jpeg *.png *.bmp)";
        QString dir = !avatarFileName.isEmpty() ? avatarFileName : QDir::homePath();
        QString fn = QFileDialog::getOpenFileName(q_func(), caption, dir, filter);
        if (fn.isEmpty())
            return;
        QImage img;
        QString err;
        if (!Texsample::testAvatar(fn, &img, &err)) {
            QMessageBox msg(q_func());
            msg.setWindowTitle(tr("Failed to change avatar", "msgbox windowTitle"));
            msg.setIcon(QMessageBox::Critical);
            msg.setText(err);
            msg.setStandardButtons(QMessageBox::Ok);
            msg.exec();
            return;
        }
        avatarFileName = fn;
        resetAvatar(img);
    }
}

/*============================================================================
================================ TUserInfoWidget =============================
============================================================================*/

/*============================== Public constructors =======================*/

TUserInfoWidget::TUserInfoWidget(Mode mode, QWidget *parent) :
    QWidget(parent), BBaseObject(*new TUserInfoWidgetPrivate(this, mode))
{
    d_func()->init();
}

TUserInfoWidget::~TUserInfoWidget()
{
    //
}

/*============================== Public methods ============================*/

TNetworkClient *TUserInfoWidget::client() const
{
    return d_func()->client;
}

QVariant TUserInfoWidget::createRequestData() const
{
    if (!hasValidInput())
        return QVariant();
    const B_D(TUserInfoWidget);
    switch (d->Mode) {
    case AddMode: {
        TAddUserRequestData data;
        data.setAccesslevel(TAccessLevel(d->cmboxAccessLevel->itemData(d->cmboxAccessLevel->currentIndex()).toInt()));
        data.setAvatar(d->avatar);
        data.setEmail(d->ledtEmail1->text());
        data.setGroups(d->groups());
        data.setLogin(d->ledtLogin->text());
        data.setName(d->ledtName->text());
        data.setPassword(Texsample::encryptPassword(d->pwdwgt1->openPassword()));
        data.setPatronymic(d->ledtPatronymic->text());
        data.setAvailableServices(d->services());
        data.setSurname(d->ledtSurname->text());
        return data;
    }
    case EditMode: {
        TEditUserRequestData data;
        data.setAccesslevel(TAccessLevel(d->cmboxAccessLevel->itemData(d->cmboxAccessLevel->currentIndex()).toInt()));
        data.setActive(d->cboxActive->isChecked());
        if (d->editAvatar)
            data.setAvatar(d->avatar);
        data.setEditAvatar(d->editAvatar);
        data.setEditEmail(d->cboxChangeEmail->isChecked());
        data.setEditPassword(d->cboxChangePassword->isChecked());
        if (d->cboxChangeEmail->isChecked())
            data.setEmail(d->ledtEmail1->text());
        data.setGroups(d->groups());
        data.setIdentifier(d->id);
        data.setName(d->ledtName->text());
        if (d->cboxChangePassword->isChecked())
            data.setPassword(Texsample::encryptPassword(d->pwdwgt1->openPassword()));
        data.setPatronymic(d->ledtPatronymic->text());
        data.setAvailableServices(d->services());
        data.setSurname(d->ledtSurname->text());
        return data;
    }
    case EditSelfMode: {
        TEditSelfRequestData data;
        if (d->editAvatar)
            data.setAvatar(d->avatar);
        data.setEditAvatar(d->editAvatar);
        data.setName(d->ledtName->text());
        data.setPatronymic(d->ledtPatronymic->text());
        data.setSurname(d->ledtSurname->text());
        return data;
    }
    case RegisterMode: {
        TRegisterRequestData data;
        data.setAvatar(d->avatar);
        data.setEmail(d->ledtEmail1->text());
        data.setInviteCode(d->ledtInvite->text());
        data.setLogin(d->ledtLogin->text());
        data.setName(d->ledtName->text());
        data.setPassword(d->pwdwgt1->openPassword());
        data.setPatronymic(d->ledtPatronymic->text());
        data.setSurname(d->ledtSurname->text());
        return data;
    }
    case ShowMode:
    default: {
        break;
    }
    }
    return QVariant();
}

bool TUserInfoWidget::hasValidInput() const
{
    return d_func()->valid;
}

TUserInfoWidget::Mode TUserInfoWidget::mode() const
{
    return d_func()->Mode;
}

TUserModel *TUserInfoWidget::model() const
{
    return d_func()->model;
}

void TUserInfoWidget::setClient(TNetworkClient *client)
{
    B_D(TUserInfoWidget);
    if (d->client) {
        disconnect(d->client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAuthorizedChanged(bool)));
        disconnect(d->client, SIGNAL(anonymousValidityChanged(bool)), d, SLOT(clientAnonymousValidityChanged(bool)));
    }
    d->client = client;
    if (client) {
        connect(client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAuthorizedChanged(bool)));
        connect(client, SIGNAL(anonymousValidityChanged(bool)), d, SLOT(clientAnonymousValidityChanged(bool)));
    }
    d->clientAuthorizedChanged(client && client->isAuthorized());
    d->clientAnonymousValidityChanged(client && client->isValid(true));
    if (EditSelfMode == d->Mode)
        setUser(d->client && d->client->isAuthorized() ? d->client->userInfo().id() : 0);
}

void TUserInfoWidget::setUser(quint64 userId)
{
    B_D(TUserInfoWidget);
    if (AddMode == d->Mode || RegisterMode == d->Mode || !d->model)
        return;
    TUserInfo info = d->model->userInfo(userId);
    d->id = info.id();
    if (d->ledtLogin)
        d->ledtLogin->setText(info.login());
    if (d->lblEmailOld)
        d->lblEmailOld->setText(info.email());
    if (d->cmboxAccessLevel)
        d->cmboxAccessLevel->setCurrentIndex(d->cmboxAccessLevel->findData(int(info.accessLevel())));
    if (d->cboxActive)
        d->cboxActive->setChecked(info.active());
    if (d->ledtName)
        d->ledtName->setText(info.name());
    if (d->ledtPatronymic)
        d->ledtPatronymic->setText(info.patronymic());
    if (d->ledtSurname)
        d->ledtSurname->setText(info.surname());
    if (d->lblRegistrationDateTime) {
        d->lblRegistrationDateTime->setText(
                    info.registrationDateTime().toLocalTime().toString(TUserInfoWidgetPrivate::DateTimeFormat));
    }
    if (d->lblLastModificationDateTime) {
        d->lblLastModificationDateTime->setText(
                    info.lastModificationDateTime().toLocalTime().toString(TUserInfoWidgetPrivate::DateTimeFormat));
    }
    d->containsAvatar = info.containsAvatar();
    d->resetAvatar(info.avatar());
    if (!d->cboxServiceMap.isEmpty()) {
        foreach (const TService &service, TServiceList::allServices())
            d->cboxServiceMap.value(service)->setChecked(info.availableServices().contains(service));
    }
    if (d->lstwgtGroups) {
        QList<TListWidget::Item> list;
        foreach (const TGroupInfo &groupInfo, info.groups()) {
            TListWidget::Item item;
            item.text = groupInfo.name();
            item.data = groupInfo.id();
            list << item;
        }
        d->lstwgtGroups->setItems(list);
    }
    d->checkInputs();
}

void TUserInfoWidget::setModel(TUserModel *model)
{
    B_D(TUserInfoWidget);
    d->model = model;
    if (EditSelfMode == d->Mode)
        setUser(d->client && d->client->isAuthorized() ? d->client->userInfo().id() : 0);
}