#include "tuserwidget.h"
#include "tuserwidget_p.h"
#include "tlistwidget.h"

#include <TeXSampleCore/TUserInfo>
#include <TeXSampleCore/TOperationResult>
#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TeXSample>
#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>

#include <BBase>
#include <BeQtGlobal>
#include <BeQtCore/private/bbase_p.h>
#include <BDirTools>
#include <BPasswordWidget>
#include <BeQt>
#include <BDialog>
#include <BTextTools>
#include <BInputField>
#include <BApplication>
#include <BPasswordGroup>
#include <BEditGroup>

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QList>
#include <QComboBox>
#include <QVariant>
#include <QVariantMap>
#include <QToolButton>
#include <QSize>
#include <QByteArray>
#include <QIcon>
#include <QPixmap>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QScrollArea>
#include <QValidator>
#include <QRegExp>
#include <QRegExpValidator>
#include <QSettings>
#include <QCheckBox>
#include <QMap>
#include <QMetaObject>
#include <QUuid>
#include <QStringList>
#include <QGroupBox>

#include <QDebug>

/*============================================================================
================================ TUserWidgetPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TUserWidgetPrivate::TUserWidgetPrivate(TUserWidget *q, TUserWidget::Mode m) :
    BBasePrivate(q), Mode(m)
{
    //
}

TUserWidgetPrivate::~TUserWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserWidgetPrivate::init()
{
    valid = false;
    id = 0;
    bool addMode = TUserWidget::AddMode == Mode;
    bool registerMode = TUserWidget::RegisterMode == Mode;
    bool editMode = TUserWidget::EditMode == Mode;
    bool showMode = TUserWidget::ShowMode == Mode;
    bool updateMode = TUserWidget::UpdateMode == Mode;
    QVBoxLayout *vlt = new QVBoxLayout(q_func());
      QHBoxLayout *hlt = new QHBoxLayout;
        QFormLayout *flt = new QFormLayout;
          ledtInvite = new QLineEdit;
            ledtInvite->setFont(BApplication::createMonospaceFont());
            ledtInvite->setInputMask("HHHHHHHH-HHHH-HHHH-HHHH-HHHHHHHHHHHH;_");
            connect(ledtInvite, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
            inputInvite = new BInputField(showMode ? BInputField::ShowNever : BInputField::ShowAlways);
            inputInvite->addWidget(ledtInvite);
          flt->addRow(tr("Invite:", "lbl text"), inputInvite);
          edtgrpEmail = new BEditGroup(this);
          ledtEmail = new QLineEdit;
            ledtEmail->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern), this));
            connect(ledtEmail, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
            inputEmail = new BInputField(showMode ? BInputField::ShowNever : BInputField::ShowAlways);
            inputEmail->addWidget(ledtEmail);
            edtgrpEmail->addEdit(ledtEmail);
          flt->addRow(tr("E-mail:", "lbl text"), inputEmail);
          ledtEmail2 = new QLineEdit;
            ledtEmail2->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern), this));
            connect(ledtEmail2, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
            inputEmail2 = new BInputField(showMode ? BInputField::ShowNever : BInputField::ShowAlways);
            inputEmail2->addWidget(ledtEmail2);
            edtgrpEmail->addEdit(ledtEmail2);
            connect(edtgrpEmail, SIGNAL(textsMatchChanged(bool)), inputEmail2, SLOT(setValid(bool)));
          flt->addRow(tr("E-mail confirmation:", "lbl text"), inputEmail2);
          ledtLogin = new QLineEdit;
            ledtLogin->setMaxLength(20);
            ledtLogin->setReadOnly(!addMode && !registerMode);
            connect(ledtLogin, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
            inputLogin = new BInputField((showMode || updateMode) ? BInputField::ShowNever : BInputField::ShowAlways);
            inputLogin->addWidget(ledtLogin);
          flt->addRow(tr("Login:", "lbl text"), inputLogin);
          pwdgrp = new BPasswordGroup(this);
          pwdwgt1 = new BPasswordWidget;
            pwdwgt1->setSavePasswordVisible(false);
            pwdwgt1->setShowPasswordVisible(false);
            pwdwgt1->setGeneratePasswordVisible(true);
            connect(pwdwgt1, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
            inputPwd1 = new BInputField(showMode ? BInputField::ShowNever : BInputField::ShowAlways);
            inputPwd1->addWidget(pwdwgt1);
            pwdgrp->addPasswordWidget(pwdwgt1);
          flt->addRow(tr("Password:", "lbl text"), inputPwd1);
          pwdwgt2 = new BPasswordWidget;
            pwdwgt2->setSavePasswordVisible(false);
            connect(pwdwgt1, SIGNAL(showPasswordChanged(bool)), pwdwgt2, SLOT(setShowPassword(bool)));
            connect(pwdwgt2, SIGNAL(showPasswordChanged(bool)), pwdwgt1, SLOT(setShowPassword(bool)));
            connect(pwdwgt2, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
            inputPwd2 = new BInputField(showMode ? BInputField::ShowNever : BInputField::ShowAlways);
            inputPwd2->addWidget(pwdwgt2);
            pwdgrp->addPasswordWidget(pwdwgt2);
          flt->addRow(tr("Password confirmation:", "lbl text"), inputPwd2);
          cmboxAccessLevel = new QComboBox;
            cmboxAccessLevel->setEnabled(addMode || editMode);
            foreach (const TAccessLevel &lvl, TAccessLevel::allAccessLevels())
                cmboxAccessLevel->addItem(lvl.toString(), (int) lvl);
            cmboxAccessLevel->setCurrentIndex(0);
          flt->addRow(tr("Access level:", "lbl text"), cmboxAccessLevel);
          ledtRealName = new QLineEdit;
            ledtRealName->setReadOnly(showMode);
            ledtRealName->setMaxLength(50);
          flt->addRow(tr("Real name:", "lbl text"), ledtRealName);
        hlt->addLayout(flt);
        QVBoxLayout *vltw = new QVBoxLayout;
          tbtnAvatar = new QToolButton;
            tbtnAvatar->setIconSize(QSize(128, 128));
            if (!showMode)
            {
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
          vltw->addWidget(tbtnAvatar);
          flt = new QFormLayout;
            foreach (const TService &s, TServiceList::allServices())
            {
                QCheckBox *cbox = new QCheckBox;
                  cbox->setEnabled(false);
                flt->addRow(tr("Access to", "lbl text") + " " + s.toString() + ":", cbox);
                cboxMap.insert(s, cbox);
            }
          vltw->addLayout(flt);
        hlt->addLayout(vltw);
      vlt->addLayout(hlt);
      gboxClab = new QGroupBox(tr("CloudLab groups", "gbox title"));
        gboxClab->setVisible(false);
        hlt = new QHBoxLayout(gboxClab);
          lstwgtClab = new TListWidget;
            lstwgtClab->setReadOnly(showMode);
            lstwgtClab->setButtonsVisible(addMode || editMode);
          hlt->addWidget(lstwgtClab);
      vlt->addWidget(gboxClab);
    //
    BApplication::setRowVisible(inputInvite, registerMode);
    BApplication::setRowVisible(inputEmail, addMode || registerMode);
    BApplication::setRowVisible(inputEmail2, addMode || registerMode);
    BApplication::setRowVisible(inputPwd1, !editMode && !showMode);
    BApplication::setRowVisible(inputPwd2, !editMode && !showMode);
    BApplication::setRowVisible(cmboxAccessLevel, !registerMode);
    foreach (QCheckBox *cbox, cboxMap)
        BApplication::setRowVisible(cbox, !registerMode);
    checkInputs();
    connect(edtgrpEmail, SIGNAL(textsMatchChanged(bool)), this, SLOT(checkInputs()));
    connect(pwdgrp, SIGNAL(passwordsMatchChanged(bool)), this, SLOT(checkInputs()));
}

/*============================== Private slots =============================*/

void TUserWidgetPrivate::resetAvatar(const QByteArray &data)
{
    avatar = data;
    if (!avatar.isEmpty())
    {
        QPixmap pm;
        pm.loadFromData(data);
        tbtnAvatar->setIcon(QIcon(pm));
        if (TUserWidget::ShowMode != Mode)
            tbtnClearAvatar->setEnabled(true);
    }
    else
    {
        tbtnAvatar->setIcon(BApplication::icon("user"));
        if (TUserWidget::ShowMode != Mode)
            tbtnClearAvatar->setEnabled(false);
    }
    if (TUserWidget::ShowMode == Mode)
    {
        tbtnAvatar->setToolTip(!avatar.isEmpty() ? tr("Click to see the picture in full size", "tbtn toolTip") :
                                                      QString());
        tbtnAvatar->setEnabled(!avatar.isEmpty());
    }
}

void TUserWidgetPrivate::checkInputs()
{
    inputInvite->setValid(!ledtInvite->text().isEmpty() && ledtInvite->hasAcceptableInput());
    inputEmail->setValid(!ledtEmail->text().isEmpty() && ledtEmail->hasAcceptableInput());
    inputLogin->setValid(!ledtLogin->text().isEmpty() && ledtLogin->hasAcceptableInput());
    inputPwd1->setValid(!pwdwgt1->encryptedPassword().isEmpty());
    inputPwd2->setValid(inputPwd1->isValid() && pwdgrp->passwordsMatch());
    bool v = q_func()->info().isValid() && (TUserWidget::ShowMode == Mode || pwdgrp->passwordsMatch());
    if (TUserWidget::RegisterMode == Mode)
        v = v && !BeQt::uuidFromText(ledtInvite->text()).isNull();
    if (v == valid)
        return;
    valid = v;
    QMetaObject::invokeMethod(q_func(), "validityChanged", Q_ARG(bool, v));
}

void TUserWidgetPrivate::tbtnAvatarClicked()
{
    if (TUserWidget::ShowMode == Mode)
    {
        BDialog dlg(q_func());
          dlg.setWindowTitle(tr("Avatar:", "dlg windowTitle") + " " + ledtLogin->text());
          dlg.addButton(QDialogButtonBox::Close, SLOT(close()));
          QScrollArea *sa = new QScrollArea;
            QLabel *lbl = new QLabel;
              QPixmap pm;
              pm.loadFromData(avatar);
              lbl->setPixmap(pm);
              lbl->setToolTip(QString::number(pm.width()) + "x" + QString::number(pm.height()));
            sa->setWidget(lbl);
          dlg.setWidget(sa);
          dlg.setMinimumSize(600, 600);
          dlg.resize(600, 600);
        dlg.exec();
    }
    else
    {
        QString caption = tr("Select file", "fdlg caption");
        QString filter = tr("Images", "fdlg filter") + " (*.jpg *.jpeg *.png *.bmp)";
        QString dir = !avatarFileName.isEmpty() ? avatarFileName : QDir::homePath();
        QString fn = QFileDialog::getOpenFileName(q_func(), caption, dir, filter);
        if (fn.isEmpty())
            return;
        if (!TUserInfo::testAvatar(fn))
        {
            QMessageBox msg(q_func());
            msg.setWindowTitle(tr("Failed to change avatar", "msgbox windowTitle"));
            msg.setIcon(QMessageBox::Critical);
            msg.setText(tr("Failed to change account avatar. The file is too big", "msgbox text"));
            QString size = BeQt::fileSizeToString(Texsample::MaximumAvatarSize, BeQt::MegabytesFormat);
            QString extent = QString::number(Texsample::MaximumAvatarExtent);
            extent.append("x" + extent + ")").prepend('(');
            msg.setInformativeText(tr("Maximum size:", "msgbox informativeText") + " " + size + " " + extent);
            msg.setStandardButtons(QMessageBox::Ok);
            msg.exec();
            return;
        }
        bool ok = false;
        QByteArray data = BDirTools::readFile(fn, -1, &ok);
        if (!ok || data.isEmpty())
        {
            QMessageBox msg(q_func());
            msg.setWindowTitle(tr("Failed to change avatar", "msgbox windowTitle"));
            msg.setIcon(QMessageBox::Critical);
            msg.setText(tr("Failed to change account avatar", "msgbox text"));
            msg.setInformativeText(tr("Some filesystem error occured", "msgbox informativeText"));
            msg.setStandardButtons(QMessageBox::Ok);
            msg.exec();
            return;
        }
        avatarFileName = fn;
        resetAvatar(data);
    }
}

/*============================================================================
================================ TUserWidget =================================
============================================================================*/

/*============================== Public constructors =======================*/

TUserWidget::TUserWidget(Mode m, QWidget *parent) :
    QWidget(parent), BBase(*new TUserWidgetPrivate(this, m))
{
    d_func()->init();
}

TUserWidget::~TUserWidget()
{
    //
}

/*============================== Public methods ============================*/

void TUserWidget::setAvailableServices(const TServiceList &list)
{
    B_D(TUserWidget);
    if (list == d->services)
        return;
    d->services = list;
    foreach (const TService &s, d->cboxMap.keys())
        d->cboxMap.value(s)->setEnabled((AddMode == d->Mode || EditMode == d->Mode) && d->services.contains(s));
}

void TUserWidget::setInfo(const TUserInfo &info)
{
    B_D(TUserWidget);
    d->id = info.id();
    d->ledtInvite->setText(info.inviteCode());
    d->ledtEmail->setText(info.email());
    d->ledtLogin->setText(info.login());
    d->pwdwgt1->setPassword(QCryptographicHash::Sha1, info.password());
    d->pwdwgt2->setPassword(QCryptographicHash::Sha1, info.password());
    d->cmboxAccessLevel->setCurrentIndex(d->cmboxAccessLevel->findData((int) info.accessLevel()));
    foreach (const TService &s, d->cboxMap.keys())
        d->cboxMap.value(s)->setChecked(info.hasAccessToService(s));
    d->ledtRealName->setText(info.realName());
    d->resetAvatar(info.avatar());
    d->checkInputs();
}

void TUserWidget::setPassword(const BPassword &pwd)
{
    d_func()->pwdwgt1->setPassword(pwd);
    d_func()->pwdwgt2->setPassword(pwd);
}

void TUserWidget::setClabGroupsVisible(bool b)
{
    d_func()->gboxClab->setVisible(b);
}

void TUserWidget::setAvailableClabGroups(const QStringList &list)
{
    d_func()->lstwgtClab->setAvailableItems(list);
}

void TUserWidget::setClabGroups(const QStringList &list)
{
    d_func()->lstwgtClab->setItems(list);
}

void TUserWidget::restorePasswordWidgetState(const QByteArray &state)
{
    d_func()->pwdwgt1->restoreWidgetState(state);
    d_func()->pwdwgt2->restoreWidgetState(state);
}

void TUserWidget::restoreState(const QByteArray &state)
{
    QVariantMap m = BeQt::deserialize(state).toMap();
    d_func()->avatarFileName = m.value("avatar_file_name").toString();
}

TUserWidget::Mode TUserWidget::mode() const
{
    return d_func()->Mode;
}

TServiceList TUserWidget::availableServices() const
{
    return d_func()->services;
}

TUserInfo TUserWidget::info() const
{
    const B_D(TUserWidget);
    TUserInfo info;
    switch (d->Mode)
    {
    case AddMode:
        info.setContext(TUserInfo::AddContext);
        break;
    case RegisterMode:
        info.setContext(TUserInfo::RegisterContext);
        break;
    case EditMode:
        info.setContext(TUserInfo::EditContext);
        break;
    case UpdateMode:
        info.setContext(TUserInfo::UpdateContext);
        break;
    case ShowMode:
        info.setContext(TUserInfo::GeneralContext);
        break;
    default:
        break;
    }
    info.setId(d->id);
    if (d->ledtInvite->hasAcceptableInput())
        info.setInviteCode(d->ledtInvite->text());
    if (d->ledtEmail->hasAcceptableInput() && d->edtgrpEmail->textsMatch())
        info.setEmail(d->ledtEmail->text());
    info.setLogin(d->ledtLogin->text());
    if (!d->pwdwgt1->encryptedPassword().isEmpty() && d->pwdgrp->passwordsMatch())
        info.setPassword(d->pwdwgt1->encryptedPassword());
    info.setAccessLevel(d->cmboxAccessLevel->itemData(d->cmboxAccessLevel->currentIndex()).toInt());
    TServiceList list;
    foreach (const TService &s, d->cboxMap.keys())
        if (d->cboxMap.value(s)->isChecked())
            list << s;
    info.setServices(list);
    info.setRealName(d->ledtRealName->text());
    if (!d->avatarFileName.isEmpty())
        info.setAvatar(d->avatarFileName);
    else
        info.setAvatar(d->avatar);
    return info;
}

BPassword TUserWidget::password() const
{
    return d_func()->pwdwgt1->password();
}

bool TUserWidget::clabGroupsVisible() const
{
    return d_func()->gboxClab->isVisible();
}

QStringList TUserWidget::availableClabGroups() const
{
    return d_func()->lstwgtClab->availableItems();
}

QStringList TUserWidget::clabGroups() const
{
    return d_func()->lstwgtClab->items();
}

QByteArray TUserWidget::savePasswordWidgetState() const
{
    return d_func()->pwdwgt1->saveWidgetState();
}

QByteArray TUserWidget::saveState() const
{
    QVariantMap m;
    m.insert("avatar_file_name", d_func()->avatarFileName);
    return BeQt::serialize(m);
}

bool TUserWidget::isValid() const
{
    return d_func()->valid;
}
