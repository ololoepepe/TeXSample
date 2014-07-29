/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleWidgets module of the TeXSample library.
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

#ifndef TRECOVERYWIDGET_P_H
#define TRECOVERYWIDGET_P_H

class BInputField;
class BPasswordGroup;
class BPasswordWidget;

class QLineEdit;
class QPushButton;

#include "trecoverywidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

/*============================================================================
================================ TRecoveryWidgetPrivate ======================
============================================================================*/

class T_WIDGETS_EXPORT TRecoveryWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TRecoveryWidget)
public:
    typedef TRecoveryWidget::RequestRecoveryCodeFunction RequestRecoveryCodeFunction;
    typedef TRecoveryWidget::RecoverAccountFunction RecoverAccountFunction;
public:
    const RequestRecoveryCodeFunction RequestFunction;
    const RecoverAccountFunction RecoverFunction;
public:
    QPushButton *btnGet;
    QPushButton *btnRecover;
    BInputField *inputCode;
    BInputField *inputEmail;
    BInputField *inputPwd1;
    BInputField *inputPwd2;
    QLineEdit *ledtCode;
    QLineEdit *ledtEmail;
    BPasswordGroup *pwdgrp;
    BPasswordWidget *pwdwgt1;
    BPasswordWidget *pwdwgt2;
public:
    explicit TRecoveryWidgetPrivate(TRecoveryWidget *q, RequestRecoveryCodeFunction requestRecoveryCodeFunction,
                                    RecoverAccountFunction recoverAccountFunction);
    ~TRecoveryWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void checkInputs();
    void getCode();
    void recoverAccount();
};

#endif // TRECOVERYWIDGET_P_H
