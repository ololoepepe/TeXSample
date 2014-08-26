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

#ifndef TCONFIRMATIONWIDGET_P_H
#define TCONFIRMATIONWIDGET_P_H

class BInputField;

class QLineEdit;

#include "tconfirmationwidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

/*============================================================================
================================ TConfirmationWidgetPrivate ==================
============================================================================*/

class T_WIDGETS_EXPORT TConfirmationWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TConfirmationWidget)
public:
    BInputField *inputCode;
    QLineEdit *ledtCode;
    bool valid;
public:
    explicit TConfirmationWidgetPrivate(TConfirmationWidget *q);
    ~TConfirmationWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void checkInputs();
};

#endif // TCONFIRMATIONWIDGET_P_H
