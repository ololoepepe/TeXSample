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

#include "tconfirmationwidget.h"
#include "tconfirmationwidget_p.h"

#include <TeXSampleCore/TeXSample>

#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BGuiTools>
#include <BInputField>
#include <BUuid>

#include <QFont>
#include <QFormLayout>
#include <QLineEdit>
#include <QMetaObject>
#include <QString>

/*============================================================================
================================ TConfirmationWidgetPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmationWidgetPrivate::TConfirmationWidgetPrivate(TConfirmationWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TConfirmationWidgetPrivate::~TConfirmationWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TConfirmationWidgetPrivate::init()
{
    valid = false;
    //
    QFormLayout *flt = new QFormLayout(q_func());
    ledtCode = new QLineEdit;
      ledtCode->setFont(BGuiTools::createMonospaceFont());
      ledtCode->setInputMask("HHHHHHHH-HHHH-HHHH-HHHH-HHHHHHHHHHHH;_");
      connect(ledtCode, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
      inputCode = new BInputField;
      inputCode->addWidget(ledtCode);
    flt->addRow(tr("Code:", "lbl text"), inputCode);
}

/*============================== Public slots ==============================*/

void TConfirmationWidgetPrivate::checkInputs()
{
    bool v = ledtCode->hasAcceptableInput();
    if (v == valid)
        return;
    inputCode->setValid(valid);
    QMetaObject::invokeMethod(q_func(), "inputValidityChanged", Q_ARG(bool, valid));
}

/*============================================================================
================================ TConfirmationWidget =========================
============================================================================*/

/*============================== Public constructors =======================*/

TConfirmationWidget::TConfirmationWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TConfirmationWidgetPrivate(this))
{
    d_func()->init();
}

TConfirmationWidget::~TConfirmationWidget()
{
    //
}

/*============================== Public methods ============================*/

BUuid TConfirmationWidget::code() const
{
    return BUuid(d_func()->ledtCode->text());
}

bool TConfirmationWidget::hasValidInput() const
{
    return d_func()->valid;
}
