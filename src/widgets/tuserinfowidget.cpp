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
#include <TeXSampleCore/TRegisterRequestData>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>
#include <TeXSampleCore/TUserIdentifier>
#include <TeXSampleCore/TUserInfo>

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

TUserInfoWidgetPrivate::TUserInfoWidgetPrivate(TUserInfoWidget *q, TUserInfoWidget::Mode m,
                                               const TAccessLevel &accessLevel) :
    BBaseObjectPrivate(q), Accesslevel(accessLevel), Mode(m)
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
      foreach (const TAccessLevel &lvl, TAccessLevel::allAccessLevels()) {
          if (TUserInfoWidget::ShowMode != Mode && lvl > Accesslevel)
              break;
          cmboxAccessLevel->addItem(lvl.toString(), int(lvl));
      }
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

void TUserInfoWidgetPrivate::createAvatarButton(QVBoxLayout *vlt, bool readOnly)
{
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
}

void TUserInfoWidgetPrivate::createEmailGroup(QFormLayout *flt, EditGroupMode mode)
{
    edtgrpEmail = new BEditGroup(this);
    if (OptionalMode == mode) {
        cboxChangeEmail = new QCheckBox;
          connect(cboxChangeEmail, SIGNAL(toggled(bool)), this, SLOT(checkInputs()));
        flt->addRow(tr("Change e-mail:", "lbl text"), cboxChangeEmail);
    }
    if (OptionalMode == mode || SeparateMode == mode) {
        ledtEmailOld = new QLineEdit;
          ledtEmailOld->setEnabled(false);
        flt->addRow(tr("Old e-mail:", "lbl text"), ledtEmailOld);
    }
    ledtEmail1 = new QLineEdit;
      ledtEmail1->setMaxLength(Texsample::MaximumEmailLength);
      ledtEmail1->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern), this));
      connect(ledtEmail1, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
      inputEmail1 = new BInputField;
      inputEmail1->addWidget(ledtEmail1);
      edtgrpEmail->addEdit(ledtEmail1);
      tbtnCheckEmail = new QToolButton;
        tbtnCheckEmail->setToolTip(tr("Check e-mail", "tbtn toolTip"));
        tbtnCheckEmail->setIcon(BApplication::icon("network"));
        connect(tbtnCheckEmail, SIGNAL(clicked()), this, SLOT(checkEmail()));
      inputEmail1->addWidget(tbtnCheckEmail);
    flt->addRow(tr("E-mail:", "lbl text"), inputEmail1);
    ledtEmail2 = new QLineEdit;
      ledtEmail1->setMaxLength(Texsample::MaximumEmailLength);
      ledtEmail2->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern), this));
      connect(ledtEmail2, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
      inputEmail2 = new BInputField;
      inputEmail2->addWidget(ledtEmail2);
      edtgrpEmail->addEdit(ledtEmail2);
      connect(edtgrpEmail, SIGNAL(textsMatchAndValidChanged(bool)), inputEmail2, SLOT(setValid(bool)));
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
      if (!readOnly) {
          tbtnCheckLogin = new QToolButton;
            tbtnCheckLogin->setToolTip(tr("Check login", "tbtn toolTip"));
            tbtnCheckLogin->setIcon(BApplication::icon("network"));
            connect(tbtnCheckLogin, SIGNAL(clicked()), this, SLOT(checkLogin()));
          inputLogin->addWidget(tbtnCheckLogin);
      }
    flt->addRow(tr("Login:", "lbl text"), inputLogin);
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
    ledtSurename = new QLineEdit;
      ledtSurename->setMaxLength(Texsample::MaximumNameLength);
      ledtSurename->setReadOnly(readOnly);
    flt->addRow(tr("Surename:", "lbl text"), ledtSurename);
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
      connect(pwdgrp, SIGNAL(passwordsMatchAndValidChanged(bool)), inputPwd2, SLOT(setValid(bool)));
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

void TUserInfoWidgetPrivate::createServicesSection(QVBoxLayout *vlt, bool readOnly)
{
    QFormLayout *flt = new QFormLayout;
    foreach (const TService &s, TServiceList::allServices()) {
        QCheckBox *cbox = new QCheckBox;
          cbox->setEnabled(!readOnly);
        flt->addRow(tr("Access to", "lbl text") + " " + s.toString() + ":", cbox);
        cboxServiceMap.insert(s, cbox);
    }
    vlt->addLayout(flt);
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
    changeEmailFunction = 0;
    changePasswordFunction = 0;
    checkEmailFunction = 0;
    checkLoginFunction = 0;
    getUserAvatarFunction = 0;
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
    ledtEmailOld = 0;
    ledtInvite = 0;
    ledtLogin = 0;
    ledtName = 0;
    ledtPatronymic = 0;
    ledtSurename = 0;
    lstwgtGroups = 0;
    pwdgrp = 0;
    pwdwgt1 = 0;
    pwdwgt2 = 0;
    pwdwgtOld = 0;
    tbtnAvatar = 0;
    tbtnCheckEmail = 0;
    tbtnCheckLogin = 0;
    tbtnClearAvatar = 0;
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
    QVBoxLayout *vlt = new QVBoxLayout;
      createAvatarButton(vlt, TUserInfoWidget::ShowMode == Mode);
      if (TUserInfoWidget::RegisterMode != Mode){
          createServicesSection(vlt, TUserInfoWidget::EditSelfMode == Mode || TUserInfoWidget::ShowMode == Mode);
          createGroupsSection(vlt, TUserInfoWidget::EditSelfMode == Mode || TUserInfoWidget::ShowMode == Mode);
      }
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

/*============================== Private slots =============================*/

void TUserInfoWidgetPrivate::changeEmail()
{
    if (!changeEmailFunction)
        return;
    QString email = ledtEmail1->text();
    TChangeEmailRequestData data;
    data.setEmail(email);
    data.setPassword(pwdwgtOld->openPassword());
    TReply r = changeEmailFunction(data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Changing e-mail failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to change e-mail. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message().messageString());
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
    if (!changePasswordFunction)
        return;
    TChangePasswordRequestData data;
    data.setOldPassword(pwdwgtOld->openPassword());
    data.setNewPassword(pwdwgt1->openPassword());
    TReply r = changePasswordFunction(data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Changing password failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to change password. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message().messageString());
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
    btnChangeEmail->setEnabled(pwdwgtOld->hasAcceptableInput() && edtgrpEmail->textsMatchAndAcceptable());
}

void TUserInfoWidgetPrivate::checkChangePasswordInputs()
{
    if (!btnChangePassword)
        return;
    inputPwdOld->setValid(pwdwgtOld->hasAcceptableInput());
    btnChangePassword->setEnabled(pwdwgtOld->hasAcceptableInput() && pwdgrp->passwordsMatchAndAcceptable());
}

void TUserInfoWidgetPrivate::checkEmail()
{
    if (!checkEmailFunction)
        return;
    QString email = ledtEmail1->text();
    TCheckEmailAvailabilityRequestData data;
    data.setEmail(email);
    TReply r = checkEmailFunction(data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Checking e-mail failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to check e-mail. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message().messageString());
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
    if (inputInvite)
        inputInvite->setValid(inviteValid);
    if (inputLogin)
        inputLogin->setValid(loginValid);
    if (tbtnCheckLogin)
        tbtnCheckLogin->setEnabled(checkLoginFunction && ledtLogin->hasAcceptableInput());
    if (inputEmail1)
        inputEmail1->setValid(ledtEmail1->hasAcceptableInput());
    if (tbtnCheckEmail)
        tbtnCheckEmail->setEnabled(changeEmailFunction && ledtEmail1->hasAcceptableInput());
    if (inputEmail2)
        inputEmail2->setValid(emailValid);
    if (inputPwd1)
        inputPwd1->setValid(pwdwgt1->hasAcceptableInput());
    if (inputPwd2)
        inputPwd2->setValid(passwordValid);
    bool v = idValid && inviteValid && loginValid && emailValid && passwordValid;
    if (v != valid) {
        valid = v;
        QMetaObject::invokeMethod(q_func(), "validityChanged", Q_ARG(bool, v));
    }
}

void TUserInfoWidgetPrivate::checkLogin()
{
    if (!checkLoginFunction)
        return;
    QString login = ledtLogin->text();
    TCheckLoginAvailabilityRequestData data;
    data.setLogin(login);
    TReply r = checkLoginFunction(data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Checking login failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to check login. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message().messageString());
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
            tbtnAvatar->setEnabled(getUserAvatarFunction);
        }
    }
    editAvatar = true;
}

void TUserInfoWidgetPrivate::tbtnAvatarClicked()
{
    if (TUserInfoWidget::ShowMode == Mode) {
        if (!containsAvatar) {
            if (!getUserAvatarFunction)
                return;
            TGetUserAvatarRequestData data;
            data.setIdentifier(id);
            TReply r = getUserAvatarFunction(data, q_func());
            if (!r) {
                QMessageBox msg(q_func());
                msg.setWindowTitle(tr("Failed to get avatar", "msgbox windowTitle"));
                msg.setIcon(QMessageBox::Critical);
                msg.setText(tr("Failed to get user avatar from server. The following error occured:", "msgbox text"));
                msg.setInformativeText(r.messageString());
                msg.setStandardButtons(QMessageBox::Ok);
                msg.exec();
                return;
            }
            avatar = r.data().value<TGetUserAvatarReplyData>().avatar();
            containsAvatar = true;
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

TUserInfoWidget::TUserInfoWidget(Mode mode, const TAccessLevel &accessLevel, QWidget *parent) :
    QWidget(parent), BBaseObject(*new TUserInfoWidgetPrivate(this, mode, accessLevel))
{
    d_func()->init();
}

TUserInfoWidget::TUserInfoWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TUserInfoWidgetPrivate(this))
{
    d_func()->init();
}

TUserInfoWidget::~TUserInfoWidget()
{
    //
}

/*============================== Public methods ============================*/

TGroupInfoList TUserInfoWidget::availableGroups() const
{
    return d_func()->availableGroups;
}

TServiceList TUserInfoWidget::availableServices() const
{
    return d_func()->availableServices;
}

TUserInfoWidget::ChangeEmailFunction TUserInfoWidget::changeEmailFunction() const
{
    return d_func()->changeEmailFunction;
}

TUserInfoWidget::ChangePasswordFunction TUserInfoWidget::changePasswordFunction() const
{
    return d_func()->changePasswordFunction;
}

TUserInfoWidget::CheckEmailFunction TUserInfoWidget::checkEmailFunction() const
{
    return d_func()->checkEmailFunction;
}

TUserInfoWidget::CheckLoginFunction TUserInfoWidget::checkLoginFunction() const
{
    return d_func()->checkLoginFunction;
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
        data.setPassword(d->pwdwgt1->openPassword());
        data.setPatronymic(d->ledtPatronymic->text());
        data.setServices(d->services());
        data.setSurename(d->ledtSurename->text());
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
            data.setPassword(d->pwdwgt1->openPassword());
        data.setPatronymic(d->ledtPatronymic->text());
        data.setServices(d->services());
        data.setSurename(d->ledtSurename->text());
        return data;
    }
    case EditSelfMode: {
        TEditSelfRequestData data;
        if (d->editAvatar)
            data.setAvatar(d->avatar);
        data.setEditAvatar(d->editAvatar);
        data.setName(d->ledtName->text());
        data.setPatronymic(d->ledtPatronymic->text());
        data.setSurename(d->ledtSurename->text());
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
        data.setSurename(d->ledtSurename->text());
        return data;
    }
    case ShowMode:
    default: {
        break;
    }
    }
    return QVariant();
}

TUserInfoWidget::GetUserAvatarFunction TUserInfoWidget::getUserAvatarFunction() const
{
    return d_func()->getUserAvatarFunction;
}

bool TUserInfoWidget::hasValidInput() const
{
    return d_func()->valid;
}

TUserInfoWidget::Mode TUserInfoWidget::mode() const
{
    return d_func()->Mode;
}

void TUserInfoWidget::setAvailableGroups(const TGroupInfoList &groups)
{
    B_D(TUserInfoWidget);
    d->availableGroups = groups;
    bRemoveDuplicates(d->availableGroups);
    if (d->lstwgtGroups) {
        QList<TListWidget::Item> list;
        foreach (const TGroupInfo &group, d->availableGroups) {
            TListWidget::Item item;
            item.text = group.name();
            item.data = group.id();
            list << item;
        }
        d->lstwgtGroups->setAvailableItems(list);
    }
}

void TUserInfoWidget::setAvailableServices(const TServiceList &services)
{
    B_D(TUserInfoWidget);
    d->availableServices = services;
    bRemoveDuplicates(d->availableServices);
    if (!d->cboxServiceMap.isEmpty() && (AddMode == d->Mode || EditMode == d->Mode)) {
        foreach (const TService &service, TServiceList::allServices())
            d->cboxServiceMap.value(service)->setEnabled(d->availableServices.contains(service));
    }
}

void TUserInfoWidget::setChangeEmailFunction(ChangeEmailFunction function)
{
    d_func()->changeEmailFunction = function;
    d_func()->checkChangeEmailInputs();
}

void TUserInfoWidget::setChangePasswordFunction(ChangePasswordFunction function)
{
    d_func()->changePasswordFunction = function;
    d_func()->checkChangePasswordInputs();
}

void TUserInfoWidget::setCheckEmailFunction(CheckEmailFunction function)
{
    d_func()->checkEmailFunction = function;
    if (d_func()->tbtnCheckEmail)
        d_func()->tbtnCheckEmail->setEnabled(function);
}

void TUserInfoWidget::setCheckLoginFunction(CheckLoginFunction function)
{
    d_func()->checkLoginFunction = function;
    if (d_func()->tbtnCheckLogin)
        d_func()->tbtnCheckLogin->setEnabled(function);
}

void TUserInfoWidget::setGetUserAvatarFunction(GetUserAvatarFunction function)
{
    d_func()->getUserAvatarFunction = function;
    if (ShowMode == d_func()->Mode && !d_func()->containsAvatar)
        d_func()->tbtnAvatar->setEnabled(function);
}

void TUserInfoWidget::setInfo(const TUserInfo &info)
{
    B_D(TUserInfoWidget);
    if (AddMode == d->Mode || RegisterMode == d->Mode)
        return;
    d->id = info.id();
    if (d->ledtLogin)
        d->ledtLogin->setText(info.login());
    if (d->ledtEmailOld)
        d->ledtEmailOld->setText(info.email());
    if (d->cmboxAccessLevel)
        d->cmboxAccessLevel->setCurrentIndex(d->cmboxAccessLevel->findData(int(info.accessLevel())));
    if (d->cboxActive)
        d->cboxActive->setChecked(info.active());
    if (d->ledtName)
        d->ledtName->setText(info.name());
    if (d->ledtPatronymic)
        d->ledtPatronymic->setText(info.patronymic());
    if (d->ledtSurename)
        d->ledtSurename->setText(info.surename());
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
            d->cboxServiceMap.value(service)->setChecked(info.services().contains(service));
    }
    if (d->lstwgtGroups) {
        QList<TListWidget::Item> list;
        foreach (quint64 groupId, info.groups()) {
            foreach (const TGroupInfo &groupInfo, d->availableGroups) {
                if (groupInfo.id() == groupId) {
                    TListWidget::Item item;
                    item.text = groupInfo.name();
                    item.data = groupId;
                    list << item;
                    break;
                }
            }
        }
        d->lstwgtGroups->setItems(list);
    }
}
