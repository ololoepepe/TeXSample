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

#ifndef TSERVICEWIDGET_P_H
#define TSERVICEWIDGET_P_H

class QCheckBox;

#include "tservicewidget.h"

#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QMap>
#include <QObject>

/*============================================================================
================================ TServiceWidgetPrivate =======================
============================================================================*/

class T_WIDGETS_EXPORT TServiceWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TServiceWidget)
public:
    TServiceList availableServices;
    QMap<TService, QCheckBox *> cboxServiceMap;
    bool readOnly;
public:
    explicit TServiceWidgetPrivate(TServiceWidget *q);
    ~TServiceWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void resetCboxes();
private:
    Q_DISABLE_COPY(TServiceWidgetPrivate)
};

#endif // TSERVICEWIDGET_P_H

