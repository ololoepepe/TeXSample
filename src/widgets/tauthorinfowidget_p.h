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

#ifndef TAUTHORINFOWIDGET_P_H
#define TAUTHORINFOWIDGET_P_H

class QFormLayout;
class BLineEdit;

#include "tauthorinfowidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>

/*============================================================================
================================ TAuthorInfoWidgetPrivate ====================
============================================================================*/

class T_WIDGETS_EXPORT TAuthorInfoWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TAuthorInfoWidget)
public:
    QFormLayout *flt;
    BLineEdit *ledtName;
    BLineEdit *ledtOrganization;
    BLineEdit *ledtPatronymic;
    BLineEdit *ledtPost;
    BLineEdit *ledtRole;
    BLineEdit *ledtSurname;
    bool valid;
public:
    explicit TAuthorInfoWidgetPrivate(TAuthorInfoWidget *q);
    ~TAuthorInfoWidgetPrivate();
public:
    void init();
    void initLineEdit(BLineEdit *&ledt, int maximimTextLength, bool required = false);
public Q_SLOTS:
    void checkInputs();
    void retranslateUi();
private:
    Q_DISABLE_COPY(TAuthorInfoWidgetPrivate)
};

#endif // TAUTHORINFOWIDGET_P_H

