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

#include "tgrouplistwidget.h"
#include "tgrouplistwidget_p.h"

#include <TeXSampleCore/TGroupInfo>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TIdList>

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>

#include <QAction>
#include <QDebug>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QObject>
#include <QSignalMapper>
#include <QString>
#include <QToolButton>
#include <QVariant>
#include <QWidget>

/*============================================================================
================================ TGroupListWidgetPrivate =====================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupListWidgetPrivate::TGroupListWidgetPrivate(TGroupListWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TGroupListWidgetPrivate::~TGroupListWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGroupListWidgetPrivate::init()
{
    readOnly = false;
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(addItem(int)));
    //
    QHBoxLayout *hlt = new QHBoxLayout(q_func());
      lstwgt = new QListWidget;
        lstwgt->setEditTriggers(QListWidget::NoEditTriggers);
        connect(lstwgt, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
                this, SLOT(lstwgtCurrentItemChanged(QListWidgetItem *)));
      hlt->addWidget(lstwgt);
      QVBoxLayout *vlt = new QVBoxLayout;
        tbtnAdd = new QToolButton;
          tbtnAdd->setMenu(new QMenu);
          tbtnAdd->setPopupMode(QToolButton::InstantPopup);
          tbtnAdd->setEnabled(false);
          tbtnAdd->setIcon(BApplication::icon("edit_add"));
          tbtnAdd->setToolTip(tr("Add...", "tbtnt toolTip"));
        vlt->addWidget(tbtnAdd);
        QHBoxLayout *hltw = new QHBoxLayout;
          tbtnRemove = new QToolButton;
            tbtnRemove->setEnabled(false);
            tbtnRemove->setIcon(BApplication::icon("editdelete"));
            tbtnRemove->setToolTip(tr("Remove selected", "tbtnt toolTip"));
            connect(tbtnRemove, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
          hltw->addWidget(tbtnRemove);
          tbtnClear = new QToolButton;
            tbtnClear->setEnabled(false);
            tbtnClear->setIcon(BApplication::icon("editclear"));
            tbtnClear->setToolTip(tr("Clear list", "tbtnt toolTip"));
            connect(tbtnClear, SIGNAL(clicked()), this, SLOT(clearList()));
          hltw->addWidget(tbtnClear);
        vlt->addLayout(hltw);
        hltw = new QHBoxLayout;
          tbtnUp = new QToolButton;
            tbtnUp->setIcon(BApplication::icon("1uparrow"));
            tbtnUp->setToolTip(tr("Move up", "tbtnt toolTip"));
            tbtnUp->setEnabled(false);
            connect(tbtnUp, SIGNAL(clicked()), this, SLOT(moveItemUp()));
          hltw->addWidget(tbtnUp);
          tbtnDown = new QToolButton;
            tbtnDown->setIcon(BApplication::icon("1downarrow"));
            tbtnDown->setToolTip(tr("Move down", "tbtnt toolTip"));
            tbtnDown->setEnabled(false);
            connect(tbtnDown, SIGNAL(clicked()), this, SLOT(moveItemDown()));
          hltw->addWidget(tbtnDown);
        vlt->addLayout(hltw);
      hlt->addLayout(vlt);
}

/*============================== Public slots ==============================*/

void TGroupListWidgetPrivate::addItem(int index)
{
    if (index < 0 || index >= availableGroups.size())
        return;
    const TGroupInfo &info = availableGroups.at(index);
    if (q_func()->groupIds().contains(info.id()))
        return;
    QListWidgetItem *lwi = new QListWidgetItem(info.name());
    lwi->setData(Qt::UserRole, info);
    lstwgt->addItem(lwi);
    lstwgtCurrentItemChanged(lstwgt->currentItem());
}

void TGroupListWidgetPrivate::clearList()
{
    lstwgt->clear();
}

void TGroupListWidgetPrivate::lstwgtCurrentItemChanged(QListWidgetItem *current)
{
    tbtnRemove->setEnabled(!readOnly && current);
    tbtnClear->setEnabled(!readOnly && lstwgt->count());
    tbtnUp->setEnabled(!readOnly && current && lstwgt->row(current) > 0);
    tbtnDown->setEnabled(!readOnly && current && (lstwgt->row(current) < lstwgt->count() - 1));
}

void TGroupListWidgetPrivate::moveItemDown()
{
    int ind = lstwgt->currentRow();
    if (ind == lstwgt->count() - 1)
        return;
    QListWidgetItem *lwi = lstwgt->takeItem(ind);
    if (!lwi)
        return;
    lstwgt->insertItem(ind + 1, lwi);
    lstwgt->setCurrentItem(lwi);
}

void TGroupListWidgetPrivate::moveItemUp()
{
    int ind = lstwgt->currentRow();
    if (!ind)
        return;
    QListWidgetItem *lwi = lstwgt->takeItem(ind);
    if (!lwi)
        return;
    lstwgt->insertItem(ind - 1, lwi);
    lstwgt->setCurrentItem(lwi);
}

void TGroupListWidgetPrivate::removeSelectedItem()
{
    delete lstwgt->takeItem(lstwgt->currentRow());
    lstwgtCurrentItemChanged(lstwgt->currentItem());
}

/*============================================================================
================================ TGroupListWidget ============================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupListWidget::TGroupListWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TGroupListWidgetPrivate(this))
{
    d_func()->init();
}

TGroupListWidget::~TGroupListWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TGroupListWidget::TGroupListWidget(TGroupListWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

TGroupInfoList TGroupListWidget::availableGroups() const
{
    return d_func()->availableGroups;
}

bool TGroupListWidget::buttonsVisible() const
{
    return d_func()->tbtnAdd->isVisible();
}

TIdList TGroupListWidget::groupIds() const
{
    TIdList list;
    foreach (const TGroupInfo &g, groups())
        list << g.id();
    return list;
}

TGroupInfoList TGroupListWidget::groups() const
{
    TGroupInfoList list;
    foreach (int i, bRangeD(0, d_func()->lstwgt->count() - 1)) {
        QListWidgetItem *item = d_func()->lstwgt->item(i);
        list << item->data(Qt::UserRole).value<TGroupInfo>();
    }
    return list;
}

bool TGroupListWidget::isReadOnly() const
{
    return d_func()->readOnly;
}

void TGroupListWidget::setAvailableGroups(const TGroupInfoList &list)
{
    B_D(TGroupListWidget);
    TIdList groups = groupIds();
    d->lstwgt->clear();
    d->tbtnAdd->menu()->clear();
    d->availableGroups = list;
    bRemoveDuplicates(d->availableGroups);
    foreach (const TGroupInfo &g, d->availableGroups) {
        if (!g.isValid())
            continue;
        QAction *act = d->tbtnAdd->menu()->addAction(g.name());
        act->setData(g);
        bSetMapping(d->mapper, act, SIGNAL(triggered()), d->tbtnAdd->menu()->actions().count() - 1);
    }
    d->tbtnAdd->setEnabled(!d->readOnly && !d->tbtnAdd->menu()->isEmpty());
    setGroups(groups);
}

void TGroupListWidget::setButtonsVisible(bool b)
{
    B_D(TGroupListWidget);
    d->tbtnAdd->setVisible(b);
    d->tbtnRemove->setVisible(b);
    d->tbtnClear->setVisible(b);
    d->tbtnUp->setVisible(b);
    d->tbtnDown->setVisible(b);
}

void TGroupListWidget::setGroups(const TGroupInfoList &list)
{
    TIdList ids;
    foreach (const TGroupInfo &g, list)
        ids << g.id();
    setGroups(ids);
}

void TGroupListWidget::setGroups(const TIdList &list)
{
    B_D(TGroupListWidget);
    d->lstwgt->clear();
    foreach (quint64 id, list) {
        foreach (int i, bRangeD(0, d->availableGroups.size() - 1)) {
            if (d->availableGroups.at(i).id() == id) {
                d->addItem(i);
                break;
            }
        }
    }
}

void TGroupListWidget::setReadOnly(bool ro)
{
    B_D(TGroupListWidget);
    d->readOnly = ro;
    d->tbtnAdd->setEnabled(!ro && !d->tbtnAdd->menu()->isEmpty());
    d->lstwgtCurrentItemChanged(d->lstwgt->currentItem());
}
