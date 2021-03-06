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

#ifndef TTAGWIDGET_P_H
#define TTAGWIDGET_P_H

class QLineEdit;
class QSignalMapper;
class QString;
class QToolButton;

#include "ttagwidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>

/*============================================================================
================================ TTagWidgetPrivate ===========================
============================================================================*/

class T_WIDGETS_EXPORT TTagWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TTagWidget)
public:
    QToolButton *tbtn;
    QLineEdit *ledt;
    QSignalMapper *mpr;
public:
    explicit TTagWidgetPrivate(TTagWidget *q);
    ~TTagWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void addTag(const QString &tag);
private:
    Q_DISABLE_COPY(TTagWidgetPrivate)
};

#endif // TTAGWIDGET_P_H

