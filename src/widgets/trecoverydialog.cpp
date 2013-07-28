#include "trecoverydialog.h"
#include "trecoverydialog_p.h"

#include <TOperationResult>

#include <BPasswordWidget>
#include <BTextTools>
#include <BInputField>
#include <BDialog>
#include <BeQtWidgets/private/bdialog_p.h>
#include <BApplication>

#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QRegExp>
#include <QString>
#include <QByteArray>

/*============================================================================
================================ TRecoveryDialogPrivate ======================
============================================================================*/

/*============================== Public constructors =======================*/

TRecoveryDialogPrivate::TRecoveryDialogPrivate(TRecoveryDialog *q, GetRecoveryCodeFunction grcf,
                                               RecoverAccountFunction raf) :
    BDialogPrivate(q), GetFunction(grcf), RecoverFunction(raf)
{
    //
}

TRecoveryDialogPrivate::~TRecoveryDialogPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRecoveryDialogPrivate::init()
{
    B_Q(TRecoveryDialog);
    q->setWindowTitle(tr("Recovering account", "windowTitle"));
    QWidget *wgt = new QWidget;
      QVBoxLayout *vlt = new QVBoxLayout(wgt);
        QGroupBox *gbox = new QGroupBox(tr("Getting recovery code", "gbox title"));
          QHBoxLayout *hlt = new QHBoxLayout;
            QLabel *lbl = new QLabel;
              lbl->setText(tr("E-mail:", "lbl text") + " ");
            hlt->addWidget(lbl);
            mledtEmail = new QLineEdit;
              mledtEmail->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern), this));
              connect(mledtEmail, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
              minputEmail = new BInputField(BInputField::ShowAlways);
              minputEmail->addWidget(mledtEmail);
            hlt->addWidget(minputEmail);
            mbtnGet = new QPushButton(tr("Get recovery code", "btn text"));
              mbtnGet->setEnabled(false);
              connect(mbtnGet, SIGNAL(clicked()), this, SLOT(getCode()));
              connect(mledtEmail, SIGNAL(returnPressed()), mbtnGet, SLOT(animateClick()));
            hlt->addWidget(mbtnGet);
          gbox->setLayout(hlt);
        vlt->addWidget(gbox);
        gbox = new QGroupBox(tr("Recovering account", "gbox title"));
          QVBoxLayout *vlt1 = new QVBoxLayout;
            QFormLayout *flt = new QFormLayout;
              mledtCode = new QLineEdit;
                mledtCode->setFont(BApplication::createMonospaceFont());
                mledtCode->setInputMask("HHHHHHHH-HHHH-HHHH-HHHH-HHHHHHHHHHHH;_");
                connect(mledtCode, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
                minputCode = new BInputField(BInputField::ShowAlways);
                minputCode->addWidget(mledtCode);
              flt->addRow(tr("Code:", "lbl text"), minputCode);
              mpwdwgt1 = new BPasswordWidget;
                mpwdwgt1->setSavePasswordVisible(false);
                mpwdwgt1->setShowPasswordVisible(false);
                mpwdwgt1->setGeneratePasswordVisible(true);
                connect(mpwdwgt1, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
                minputPwd1 = new BInputField(BInputField::ShowAlways);
                minputPwd1->addWidget(mpwdwgt1);
              flt->addRow(tr("Password:", "lbl text"), minputPwd1);
              mpwdwgt2 = new BPasswordWidget;
                mpwdwgt2->setSavePasswordVisible(false);
                connect(mpwdwgt1, SIGNAL(showPasswordChanged(bool)), mpwdwgt2, SLOT(setShowPassword(bool)));
                connect(mpwdwgt2, SIGNAL(showPasswordChanged(bool)), mpwdwgt1, SLOT(setShowPassword(bool)));
                connect(mpwdwgt2, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
                minputPwd2 = new BInputField(BInputField::ShowAlways);
                minputPwd2->addWidget(mpwdwgt2);
              flt->addRow(tr("Password confirmation:", "lbl text"), minputPwd2);
            vlt1->addLayout(flt);
          gbox->setLayout(vlt1);
          hlt = new QHBoxLayout;
            hlt->addStretch();
            mbtnRecover = new QPushButton(tr("Recover account", "btn text"));
              mbtnRecover->setEnabled(false);
              connect(mbtnRecover, SIGNAL(clicked()), this, SLOT(recoverAccount()));
              connect(mledtCode, SIGNAL(returnPressed()), mbtnRecover, SLOT(animateClick()));
            hlt->addWidget(mbtnRecover);
          vlt1->addLayout(hlt);
        vlt->addWidget(gbox);
    q->setWidget(wgt);
    q->addButton(QDialogButtonBox::Close, SLOT(close()));
    q->setMinimumWidth(650);
    q->setFixedHeight(q->sizeHint().height());
}

/*============================== Public slots ==============================*/

void TRecoveryDialogPrivate::checkInputs()
{
    minputEmail->setValid(!mledtEmail->text().isEmpty() && mledtEmail->hasAcceptableInput());
    minputCode->setValid(mledtCode->hasAcceptableInput());
    mbtnGet->setEnabled(minputEmail->isValid() && mledtCode->text() == "----");
    minputPwd1->setValid(!mpwdwgt1->encryptedPassword().isEmpty());
    bool pwdm = mpwdwgt1->encryptedPassword() == mpwdwgt2->encryptedPassword();
    minputPwd2->setValid(minputPwd1->isValid() && pwdm);
    mbtnRecover->setEnabled(minputCode->isValid() && minputPwd1->isValid() && minputPwd2->isValid());
}

void TRecoveryDialogPrivate::getCode()
{
    if (!GetFunction)
        return;
    static QMessageBox *msg = 0;
    if (msg)
        return;
    QString email = mledtEmail->text();
    if (email.isEmpty())
        return;
    msg = new QMessageBox(q_func());
    msg->setWindowTitle(tr("Getting recovery code", "msgbox windowTitle"));
    msg->setIcon(QMessageBox::Question);
    msg->setText(tr("You are going to get a recovery code. Do you want to continue?", "msgbox text"));
    msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg->setDefaultButton(QMessageBox::Yes);
    bool b = QMessageBox::Yes == msg->exec();
    delete msg;
    msg = 0;
    if (!b)
        return;
    TOperationResult r = GetFunction(email, q_func());
    if (r)
    {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Recovery code generated", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Information);
        msg.setText(tr("Account recovery code was generated and sent to your e-mail", "msgbox text"));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
    else
    {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Getting recovery code error", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to get recovery code due to the following error:", "msgbox text"));
        msg.setInformativeText(r.messageString());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
}

void TRecoveryDialogPrivate::recoverAccount()
{
    if (!RecoverFunction)
        return;
    static QMessageBox *msg = 0;
    if (msg)
        return;
    QString email = mledtEmail->text();
    QString code = mledtCode->text();
    QByteArray password = mpwdwgt1->encryptedPassword();
    if (email.isEmpty() || code.isEmpty() || password.isEmpty() || mpwdwgt2->encryptedPassword() != password)
        return;
    msg = new QMessageBox(q_func());
    msg->setWindowTitle(tr("Recovering account", "msgbox windowTitle"));
    msg->setIcon(QMessageBox::Question);
    msg->setText(tr("You are going to recover your accont. Do you want to continue?", "msgbox text"));
    msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg->setDefaultButton(QMessageBox::Yes);
    bool b = QMessageBox::Yes == msg->exec();
    delete msg;
    msg = 0;
    if (!b)
        return;
    TOperationResult r = RecoverFunction(email, code, password, q_func());
    if (r)
    {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Account recovered", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Information);
        msg.setText(tr("Account recovery completed. Please, check your e-mail", "msgbox text"));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
    else
    {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Account recovering error", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to recover account due to the following error:", "msgbox text"));
        msg.setInformativeText(r.messageString());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
}

/*============================================================================
================================ TRecoveryDialog =============================
============================================================================*/

/*============================== Public constructors =======================*/

TRecoveryDialog::TRecoveryDialog(GetRecoveryCodeFunction grcf, RecoverAccountFunction raf, QWidget *parent) :
    BDialog(*new TRecoveryDialogPrivate(this, grcf, raf), parent)
{
    d_func()->init();
}

TRecoveryDialog::~TRecoveryDialog()
{
    //
}
