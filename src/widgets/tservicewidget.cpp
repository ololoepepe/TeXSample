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

#include "tservicewidget.h"
#include "tservicewidget_p.h"

#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BGuiTools>

#include <QCheckBox>
#include <QDebug>
#include <QFormLayout>
#include <QLabel>
#include <QList>
#include <QMap>
#include <QString>
#include <QWidget>

/*============================================================================
================================ TServiceWidgetPrivate =======================
============================================================================*/

/*============================== Public constructors =======================*/

TServiceWidgetPrivate::TServiceWidgetPrivate(TServiceWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TServiceWidgetPrivate::~TServiceWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TServiceWidgetPrivate::init()
{
    readOnly = false;
    //
    QFormLayout *flt = new QFormLayout(q_func());
    foreach (const TService &s, TServiceList::allServices()) {
        QCheckBox *cbox = new QCheckBox;
        flt->addRow(" ", cbox);
        cboxServiceMap.insert(s, cbox);
    }
    //
    connect(bApp, SIGNAL(languageChanged()), this, SLOT(resetCboxes()));
    resetCboxes();
}

/*============================== Public slots ==============================*/

void TServiceWidgetPrivate::resetCboxes()
{
    foreach (const TService &s, TServiceList::allServices()) {
        QCheckBox *cbox = cboxServiceMap.value(s);
        cbox->setEnabled(!readOnly && availableServices.contains(s));
        BGuiTools::labelForField<QLabel>(cbox)->setText(tr("Access to", "lbl text") + " " + s.toString() + ":");
    }
}

/*============================================================================
================================ TServiceWidget ==============================
============================================================================*/

/*============================== Public constructors =======================*/

TServiceWidget::TServiceWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TServiceWidgetPrivate(this))
{
    d_func()->init();
}

TServiceWidget::~TServiceWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TServiceWidget::TServiceWidget(TServiceWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

TServiceList TServiceWidget::availableServices() const
{
    return d_func()->availableServices;
}

bool TServiceWidget::isReadOnly() const
{
    return d_func()->readOnly;
}

void TServiceWidget::setAvailableServices(const TServiceList &list)
{
    d_func()->availableServices = list;
    d_func()->resetCboxes();
}

void TServiceWidget::setReadOnly(bool ro)
{
    d_func()->readOnly = ro;
    d_func()->resetCboxes();
}

void TServiceWidget::setServices(const TServiceList &list)
{
    foreach (const TService &s, TServiceList::allServices())
        d_func()->cboxServiceMap.value(s)->setChecked(list.contains(s));
}

TServiceList TServiceWidget::services() const
{
    TServiceList list;
    foreach (const TService &s, TServiceList::allServices()) {
        if (d_func()->cboxServiceMap.value(s)->isChecked())
            list << s;
    }
    return list;
}
