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

#include "trecoverywidget.h"
#include "trecoverywidget_p.h"

#include <TeXSampleCore/TMessage>
#include <TeXSampleCore/TeXSample>
#include <TeXSampleCore/TOperation>
#include <TeXSampleCore/TRecoverAccountRequestData>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TRequestRecoveryCodeRequestData>
#include <TeXSampleNetwork/TNetworkClient>

#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BGuiTools>
#include <BInputField>
#include <BPasswordGroup>
#include <BPasswordWidget>
#include <BTextTools>

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QString>
#include <QValidator>
#include <QVBoxLayout>

/*============================================================================
================================ TRecoveryWidgetPrivate ======================
============================================================================*/

/*============================== Public constructors =======================*/

TRecoveryWidgetPrivate::TRecoveryWidgetPrivate(TRecoveryWidget *q, TNetworkClient *client) :
    BBaseObjectPrivate(q), Client(client)
{
    //
}

TRecoveryWidgetPrivate::~TRecoveryWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TRecoveryWidgetPrivate::init()
{
    if (Client)
        connect(Client, SIGNAL(anonymousValidityChanged(bool)), this, SLOT(checkInputs()));
    B_Q(TRecoveryWidget);
    QVBoxLayout *vlt = new QVBoxLayout(q);
      QGroupBox *gbox = new QGroupBox(tr("Getting recovery code", "gbox title"));
        QHBoxLayout *hlt = new QHBoxLayout;
          QLabel *lbl = new QLabel;
            lbl->setText(tr("E-mail:", "lbl text") + " ");
          hlt->addWidget(lbl);
          ledtEmail = new QLineEdit;
            ledtEmail->setValidator(new QRegExpValidator(BTextTools::standardRegExp(BTextTools::EmailPattern),
                                                         this));
            connect(ledtEmail, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
            inputEmail = new BInputField(BInputField::ShowAlways);
            inputEmail->addWidget(ledtEmail);
          hlt->addWidget(inputEmail);
          btnGet = new QPushButton(tr("Get recovery code", "btn text"));
            btnGet->setEnabled(false);
            connect(btnGet, SIGNAL(clicked()), this, SLOT(getCode()));
            connect(ledtEmail, SIGNAL(returnPressed()), btnGet, SLOT(animateClick()));
          hlt->addWidget(btnGet);
        gbox->setLayout(hlt);
      vlt->addWidget(gbox);
      gbox = new QGroupBox(tr("Recovering account", "gbox title"));
        QVBoxLayout *vlt1 = new QVBoxLayout;
          QFormLayout *flt = new QFormLayout;
            ledtCode = new QLineEdit;
              ledtCode->setFont(BGuiTools::createMonospaceFont());
              ledtCode->setInputMask("HHHHHHHH-HHHH-HHHH-HHHH-HHHHHHHHHHHH;_");
              connect(ledtCode, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
              inputCode = new BInputField;
              inputCode->addWidget(ledtCode);
            flt->addRow(tr("Code:", "lbl text"), inputCode);
            QRegExp rx(".{" + QString::number(Texsample::MinimumPasswordLength) + ","
                       + QString::number(Texsample::MaximumPasswordLength) + "}");
            pwdgrp = new BPasswordGroup(this);
            pwdwgt1 = new BPasswordWidget;
              pwdwgt1->setSavePasswordVisible(false);
              pwdwgt1->setShowPasswordVisible(false);
              pwdwgt1->setGeneratePasswordVisible(true);
              pwdwgt1->setValidator(new QRegExpValidator(rx, this));
              connect(pwdwgt1, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
              inputPwd1 = new BInputField;
              inputPwd1->addWidget(pwdwgt1);
              pwdgrp->addPasswordWidget(pwdwgt1);
            flt->addRow(tr("Password:", "lbl text"), inputPwd1);
            pwdwgt2 = new BPasswordWidget;
              pwdwgt2->setSavePasswordVisible(false);
              pwdwgt2->setValidator(new QRegExpValidator(rx, this));
              connect(pwdwgt1, SIGNAL(showPasswordChanged(bool)), pwdwgt2, SLOT(setShowPassword(bool)));
              connect(pwdwgt2, SIGNAL(showPasswordChanged(bool)), pwdwgt1, SLOT(setShowPassword(bool)));
              connect(pwdwgt2, SIGNAL(passwordChanged()), this, SLOT(checkInputs()));
              inputPwd2 = new BInputField;
              inputPwd2->addWidget(pwdwgt2);
              pwdgrp->addPasswordWidget(pwdwgt2);
              connect(pwdgrp, SIGNAL(passwordsMatchAndValidChanged(bool)), inputPwd2, SLOT(setValid(bool)));
            flt->addRow(tr("Password confirmation:", "lbl text"), inputPwd2);
          vlt1->addLayout(flt);
        gbox->setLayout(vlt1);
        hlt = new QHBoxLayout;
          hlt->addStretch();
          btnRecover = new QPushButton(tr("Recover account", "btn text"));
            btnRecover->setEnabled(false);
            connect(btnRecover, SIGNAL(clicked()), this, SLOT(recoverAccount()));
            connect(ledtCode, SIGNAL(returnPressed()), btnRecover, SLOT(animateClick()));
          hlt->addWidget(btnRecover);
        vlt1->addLayout(hlt);
      vlt->addWidget(gbox);
}

/*============================== Public slots ==============================*/

void TRecoveryWidgetPrivate::checkInputs()
{
    bool emailValid = ledtEmail->hasAcceptableInput();
    bool codeValid = ledtCode->hasAcceptableInput();
    inputEmail->setValid(emailValid);
    inputCode->setValid(codeValid);
    btnGet->setEnabled(Client && Client->isValid(true) && emailValid);
    inputPwd1->setValid(pwdwgt1->hasAcceptableInput());
    btnRecover->setEnabled(Client && Client->isValid(true) && codeValid && pwdgrp->passwordsMatchAndAcceptable());
}

void TRecoveryWidgetPrivate::getCode()
{
    if (!Client || !Client->isValid(true))
        return;
    static QMessageBox *msg = 0;
    if (msg)
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
    TRequestRecoveryCodeRequestData data;
    data.setEmail(ledtEmail->text());
    TReply r = Client->performAnonymousOperation(TOperation::RequestRecoveryCode, data, q_func());
    if (r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Recovery code generated", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Information);
        msg.setText(tr("Account recovery code was generated and sent to your e-mail", "msgbox text"));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    } else {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Getting recovery code error", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to get recovery code due to the following error:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
}

void TRecoveryWidgetPrivate::recoverAccount()
{
    if (!Client || !Client->isValid(true))
        return;
    static QMessageBox *msg = 0;
    if (msg)
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
    TRecoverAccountRequestData data;
    data.setPassword(pwdwgt1->openPassword());
    data.setRecoveryCode(ledtCode->text());
    TReply r = Client->performAnonymousOperation(TOperation::RecoverAccount, data, q_func());
    if (r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Account recovered", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Information);
        msg.setText(tr("Account recovery completed. Please, check your e-mail", "msgbox text"));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    } else {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Account recovering error", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to recover account due to the following error:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
}

/*============================================================================
================================ TRecoveryWidget =============================
============================================================================*/

/*============================== Public constructors =======================*/

TRecoveryWidget::TRecoveryWidget(TNetworkClient *client, QWidget *parent) :
    QWidget(parent), BBaseObject(*new TRecoveryWidgetPrivate(this, client))
{
    d_func()->init();
}

TRecoveryWidget::~TRecoveryWidget()
{
    //
}
