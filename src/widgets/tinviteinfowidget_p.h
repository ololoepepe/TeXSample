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

#ifndef TINVITEINFOWIDGET_P_H
#define TINVITEINFOWIDGET_P_H

class TGroupListWidget;
class TServiceWidget;

class QComboBox;
class QDateTimeEdit;
class QGroupBox;
class QLabel;
class QSpinBox;

#include "tinviteinfowidget.h"

#include <TeXSampleCore/TAccessLevel>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QList>
#include <QObject>

/*============================================================================
================================ TInviteInfoWidgetPrivate ====================
============================================================================*/

class T_WIDGETS_EXPORT TInviteInfoWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TInviteInfoWidget)
public:
    QList<TAccessLevel> availableAccessLevels;
    QComboBox *cmboxAccessLevel;
    QDateTimeEdit *dtedtExpires;
    QGroupBox *gboxServices;
    QGroupBox *gboxGroups;
    TGroupListWidget *glwgt;
    QLabel *lblCode;
    QLabel *lblCreationDateTime;
    QLabel *lblOwnerLogin;
    quint16 maxInviteCount;
    bool readOnly;
    QSpinBox *sboxCount;
    TServiceWidget *swgt;
    bool valid;
public:
    explicit TInviteInfoWidgetPrivate(TInviteInfoWidget *q);
    ~TInviteInfoWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void retranslateUi();
private:
    Q_DISABLE_COPY(TInviteInfoWidgetPrivate)
};

#endif // TINVITEINFOWIDGET_P_H
