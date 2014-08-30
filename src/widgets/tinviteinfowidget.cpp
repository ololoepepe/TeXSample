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

#include "tinviteinfowidget.h"
#include "tinviteinfowidget_p.h"

#include "tgrouplistwidget.h"
#include "tservicewidget.h"

#include <TeXSampleCore/TeXSample>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TIdList>
#include <TeXSampleCore/TInviteInfo>
#include <TeXSampleCore/TServiceList>

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BGuiTools>
#include <BUuid>

#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QDebug>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QMetaObject>
#include <QSpinBox>
#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

#include <climits>

/*============================================================================
================================ TInviteInfoWidgetPrivate ====================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteInfoWidgetPrivate::TInviteInfoWidgetPrivate(TInviteInfoWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TInviteInfoWidgetPrivate::~TInviteInfoWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TInviteInfoWidgetPrivate::init()
{
    maxInviteCount = 0;
    readOnly = false;
    //
    QVBoxLayout *vlt = new QVBoxLayout(q_func());
      QFormLayout *flt = new QFormLayout;
        lblCode = new QLabel;
        flt->addRow(" ", lblCode);
        lblOwnerLogin = new QLabel;
        flt->addRow(" ", lblOwnerLogin);
        cmboxAccessLevel = new QComboBox;
          foreach (const TAccessLevel &lvl, TAccessLevel::allAccessLevels()) {
              availableAccessLevels << lvl;
              cmboxAccessLevel->addItem(lvl.toString(), int(lvl));
          }
          cmboxAccessLevel->setCurrentIndex(0);
        flt->addRow(" ", cmboxAccessLevel);
        lblCreationDateTime = new QLabel;
        flt->addRow(" ", lblCreationDateTime);
        dtedtExpires = new QDateTimeEdit;
          dtedtExpires->setMinimumDateTime(QDateTime::currentDateTime().addDays(1));
          dtedtExpires->setDateTime(QDateTime::currentDateTime().addDays(3));
          dtedtExpires->setDisplayFormat("dd MMMM yyyy hh:mm");
          dtedtExpires->setCalendarPopup(true);
        flt->addRow(" ", dtedtExpires);
        sboxCount = new QSpinBox;
          sboxCount->setMinimum(1);
          sboxCount->setMaximum(quint16(USHRT_MAX));
          sboxCount->setValue(1);
        flt->addRow(" ", sboxCount);
      vlt->addLayout(flt);
      gboxServices = new QGroupBox;
        QHBoxLayout *hlt = new QHBoxLayout(gboxServices);
          swgt = new TServiceWidget;
          hlt->addWidget(swgt);
      vlt->addWidget(gboxServices);
      gboxGroups = new QGroupBox;
        hlt = new QHBoxLayout(gboxGroups);
          glwgt = new TGroupListWidget;
          hlt->addWidget(glwgt);
      vlt->addWidget(gboxGroups);
    //
    BGuiTools::setRowVisible(lblCode, false);
    BGuiTools::setRowVisible(lblCreationDateTime, false);
    BGuiTools::setRowVisible(lblOwnerLogin, false);
    retranslateUi();
    connect(bApp, SIGNAL(languageChanged()), this, SLOT(retranslateUi()));
}

/*============================== Public slots ==============================*/

void TInviteInfoWidgetPrivate::retranslateUi()
{
    BGuiTools::labelForField<QLabel>(lblCode)->setText(tr("Code:", "lbl text"));
    BGuiTools::labelForField<QLabel>(lblOwnerLogin)->setText(tr("Owner login:", "lbl text"));
    BGuiTools::labelForField<QLabel>(cmboxAccessLevel)->setText(tr("Access level:", "lbl text"));
    BGuiTools::labelForField<QLabel>(lblCreationDateTime)->setText(tr("Creation date:", "lbl text"));
    BGuiTools::labelForField<QLabel>(dtedtExpires)->setText(tr("Expiration date:", "lbl text"));
    BGuiTools::labelForField<QLabel>(sboxCount)->setText(tr("Count:", "lbl text"));
    gboxServices->setTitle(tr("Services", "gbox title"));
    gboxGroups->setTitle(tr("Groups", "gbox title"));
}

/*============================================================================
================================ TInviteInfoWidget ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteInfoWidget::TInviteInfoWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TInviteInfoWidgetPrivate(this))
{
    d_func()->init();
}

TInviteInfoWidget::~TInviteInfoWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TInviteInfoWidget::TInviteInfoWidget(TInviteInfoWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

TAccessLevel TInviteInfoWidget::accessLevel() const
{
    return d_func()->cmboxAccessLevel->itemData(d_func()->cmboxAccessLevel->currentIndex()).toInt();
}

QList<TAccessLevel> TInviteInfoWidget::availableAccessLevels() const
{
    return d_func()->availableAccessLevels;
}

TGroupInfoList TInviteInfoWidget::availableGroups() const
{
    return d_func()->glwgt->availableGroups();
}

TServiceList TInviteInfoWidget::availableServices() const
{
    return d_func()->swgt->availableServices();
}

quint16 TInviteInfoWidget::count() const
{
    return quint16(d_func()->sboxCount->value());
}

QDateTime TInviteInfoWidget::expirationDateTime() const
{
    return d_func()->dtedtExpires->dateTime().toUTC();
}

TGroupInfoList TInviteInfoWidget::groups() const
{
    return d_func()->glwgt->groups();
}

TIdList TInviteInfoWidget::groupIds() const
{
    return d_func()->glwgt->groupIds();
}

bool TInviteInfoWidget::isReadOnly() const
{
    return d_func()->readOnly;
}

quint16 TInviteInfoWidget::maxInviteCount() const
{
    return d_func()->maxInviteCount;
}

TServiceList TInviteInfoWidget::services() const
{
    return d_func()->swgt->services();
}

void TInviteInfoWidget::setAvailableAccessLevels(const QList<TAccessLevel> &list)
{
    B_D(TInviteInfoWidget);
    if (!d->readOnly)
        return;
    d->availableAccessLevels = list;
    foreach (int i, bRangeD(0, d->cmboxAccessLevel->count() - 1)) {
        TAccessLevel lvl(d->cmboxAccessLevel->itemData(i).toInt());
        BGuiTools::setItemEnabled(d->cmboxAccessLevel, i, list.contains(lvl));
    }
}

void TInviteInfoWidget::setAvailableGroups(const TGroupInfoList &list)
{
    if (d_func()->readOnly)
        return;
    d_func()->glwgt->setAvailableGroups(list);
}

void TInviteInfoWidget::setAvailableServices(const TServiceList &list)
{
    if (d_func()->readOnly)
        return;
    d_func()->swgt->setAvailableServices(list);
}

void TInviteInfoWidget::setExpirationDateTime(const QDateTime &dt)
{
    d_func()->dtedtExpires->setDateTime(dt);
}

void TInviteInfoWidget::setGroups(const TGroupInfoList &list)
{
    if (d_func()->readOnly)
        d_func()->glwgt->setAvailableGroups(list);
    d_func()->glwgt->setGroups(list);
}

void TInviteInfoWidget::setGroups(const TIdList &list)
{
    if (d_func()->readOnly)
        return;
    d_func()->glwgt->setGroups(list);
}

void TInviteInfoWidget::setInfo(const TInviteInfo &info)
{
    B_D(TInviteInfoWidget);
    if (!d->readOnly)
        return;
    foreach (int i, bRangeD(0, d->cmboxAccessLevel->count() - 1)) {
        if (d->cmboxAccessLevel->itemData(i).toInt() == info.accessLevel().level()) {
            d->cmboxAccessLevel->setCurrentIndex(i);
            break;
        }
    }
    d->lblCode->setText(info.code().toString(true));
    d->lblCreationDateTime->setText(info.creationDateTime().toString("dd MMMM yyyy hh:mm"));
    d->dtedtExpires->setDateTime(info.expirationDateTime());
    d->glwgt->setAvailableGroups(info.groups());
    d->glwgt->setGroups(info.groups());
    d->lblOwnerLogin->setText(info.ownerLogin());
    d->swgt->setServices(info.services());
}

void TInviteInfoWidget::setMaxInviteCount(quint16 count)
{
    d_func()->maxInviteCount = count;
    d_func()->sboxCount->setMaximum(count ? count : quint16(USHRT_MAX));
}

void TInviteInfoWidget::setReadOnly(bool ro)
{
    B_D(TInviteInfoWidget);
    d->readOnly = ro;
    if (ro) {
        d->availableAccessLevels.clear();
        foreach (int i, bRangeD(0, d->cmboxAccessLevel->count() - 1))
            BGuiTools::setItemEnabled(d->cmboxAccessLevel, i, true);
        d->cmboxAccessLevel->setEnabled(false);
        d->dtedtExpires->setMinimumDateTime(QDateTime());
        d->dtedtExpires->setReadOnly(true);
        d->glwgt->setAvailableGroups(TGroupInfoList());
        d->glwgt->setReadOnly(true);
        BGuiTools::setRowVisible(d->lblCode, true);
        BGuiTools::setRowVisible(d->lblCreationDateTime, true);
        BGuiTools::setRowVisible(d->lblOwnerLogin, true);
        BGuiTools::setRowVisible(d->sboxCount, false);
        d->swgt->setAvailableServices(TServiceList());
        d->swgt->setReadOnly(true);
    } else {
        d->cmboxAccessLevel->setEnabled(true);
        d->cmboxAccessLevel->setCurrentIndex(0);
        d->dtedtExpires->setMinimumDateTime(QDateTime::currentDateTime().addDays(1));
        d->dtedtExpires->setDateTime(QDateTime::currentDateTime().addDays(3));
        d->dtedtExpires->setReadOnly(false);
        d->glwgt->setReadOnly(false);
        BGuiTools::setRowVisible(d->lblCode, false);
        BGuiTools::setRowVisible(d->lblCreationDateTime, false);
        BGuiTools::setRowVisible(d->lblOwnerLogin, false);
        BGuiTools::setRowVisible(d->sboxCount, true);
        d->swgt->setReadOnly(false);
    }
}

void TInviteInfoWidget::setServices(const TServiceList &list)
{
    d_func()->swgt->setServices(list);
}
