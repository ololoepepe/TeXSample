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

#include "tauthorlistwidget.h"
#include "tauthorlistwidget_p.h"

#include "tauthorinfowidget.h"

#include <TeXSampleCore/TAuthorInfo>
#include <TeXSampleCore/TAuthorInfoList>

#include <BApplication>
#include <BBaseObject>
#include <BDialog>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BTextTools>

#include <QAction>
#include <QDebug>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QToolButton>
#include <QVariant>
#include <QWidget>

/*============================================================================
================================ TAuthorListWidgetPrivate ====================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorListWidgetPrivate::TAuthorListWidgetPrivate(TAuthorListWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TAuthorListWidgetPrivate::~TAuthorListWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorListWidgetPrivate::addItem(const TAuthorInfo &info)
{
    QListWidgetItem *lwi = new QListWidgetItem;
    resetItem(lwi, info);
    lstwgt->addItem(lwi);
    lstwgtCurrentItemChanged(lstwgt->currentItem());
}

void TAuthorListWidgetPrivate::init()
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
        connect(lstwgt, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(editItem(QListWidgetItem *)));
      hlt->addWidget(lstwgt);
      QVBoxLayout *vlt = new QVBoxLayout;
        tbtnAdd = new QToolButton;
          tbtnAdd->setMenu(new QMenu);
          tbtnAdd->setPopupMode(QToolButton::MenuButtonPopup);
          tbtnAdd->menu()->setEnabled(false);
          tbtnAdd->setIcon(BApplication::icon("edit_add"));
          tbtnAdd->setToolTip(tr("Add...", "tbtnt toolTip"));
          connect(tbtnAdd, SIGNAL(clicked()), this, SLOT(addItem()));
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

void TAuthorListWidgetPrivate::resetItem(QListWidgetItem *item, const TAuthorInfo &info)
{
    if (!item || !info.isValid())
        return;
    QString s = info.organization();
    if (!s.isEmpty() && !info.post().isEmpty())
        s += ", ";
    s += info.post();
    BTextTools::wrap(s, "[", "]");
    item->setText(info.fullName());
    item->setToolTip(info.role() + ((!s.isEmpty() && !info.role().isEmpty()) ? " " : "") + s);
    item->setData(Qt::UserRole, info);
}

/*============================== Public slots ==============================*/

void TAuthorListWidgetPrivate::addItem()
{
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Adding author", "dlg windowTitle"));
    TAuthorInfoWidget *aiwgt = new TAuthorInfoWidget;
    dlg.setWidget(aiwgt);
    dlg.resize(400, 0);
    dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
    QPushButton *btnAccept = dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()));
    btnAccept->setEnabled(aiwgt->hasValidInput());
    connect(aiwgt, SIGNAL(inputValidityChanged(bool)), btnAccept, SLOT(setEnabled(bool)));
    if (dlg.exec() != BDialog::Accepted)
        return;
    addItem(aiwgt->info());
}

void TAuthorListWidgetPrivate::addItem(int index)
{
    if (index < 0 || index >= availableAuthors.size())
        return;
    const TAuthorInfo &info = availableAuthors.at(index);
    if (q_func()->authors().contains(info))
        return;
    addItem(info);
}

void TAuthorListWidgetPrivate::clearList()
{
    lstwgt->clear();
}

void TAuthorListWidgetPrivate::editItem(QListWidgetItem *item)
{
    if (!item)
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(readOnly ? tr("Author info", "dlg windowTitle") : tr("Editing author", "dlg windowTitle"));
    TAuthorInfoWidget *aiwgt = new TAuthorInfoWidget;
    aiwgt->setReadOnly(readOnly);
    aiwgt->setInfo(item->data(Qt::UserRole).value<TAuthorInfo>());
    dlg.setWidget(aiwgt);
    dlg.resize(400, 0);
    if (readOnly) {
        dlg.addButton(QDialogButtonBox::Close, SLOT(close()));
        dlg.exec();
    } else {
        dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
        QPushButton *btnAccept = dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()));
        btnAccept->setEnabled(aiwgt->hasValidInput());
        connect(aiwgt, SIGNAL(inputValidityChanged(bool)), btnAccept, SLOT(setEnabled(bool)));
        if (dlg.exec() != BDialog::Accepted)
            return;
        resetItem(item, aiwgt->info());
    }
}

void TAuthorListWidgetPrivate::lstwgtCurrentItemChanged(QListWidgetItem *current)
{
    tbtnRemove->setEnabled(!readOnly && current);
    tbtnClear->setEnabled(!readOnly && lstwgt->count());
    tbtnUp->setEnabled(!readOnly && current && lstwgt->row(current) > 0);
    tbtnDown->setEnabled(!readOnly && current && (lstwgt->row(current) < lstwgt->count() - 1));
}

void TAuthorListWidgetPrivate::moveItemDown()
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

void TAuthorListWidgetPrivate::moveItemUp()
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

void TAuthorListWidgetPrivate::removeSelectedItem()
{
    delete lstwgt->takeItem(lstwgt->currentRow());
    lstwgtCurrentItemChanged(lstwgt->currentItem());
}

/*============================================================================
================================ TAuthorListWidget ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorListWidget::TAuthorListWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TAuthorListWidgetPrivate(this))
{
    d_func()->init();
}

TAuthorListWidget::~TAuthorListWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TAuthorListWidget::TAuthorListWidget(TAuthorListWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

TAuthorInfoList TAuthorListWidget::availableAuthors() const
{
    return d_func()->availableAuthors;
}

bool TAuthorListWidget::buttonsVisible() const
{
    return d_func()->tbtnAdd->isVisible();
}

TAuthorInfoList TAuthorListWidget::authors() const
{
    TAuthorInfoList list;
    foreach (int i, bRangeD(0, d_func()->lstwgt->count() - 1)) {
        QListWidgetItem *item = d_func()->lstwgt->item(i);
        list << item->data(Qt::UserRole).value<TAuthorInfo>();
    }
    return list;
}

bool TAuthorListWidget::isReadOnly() const
{
    return d_func()->readOnly;
}

void TAuthorListWidget::setAvailableAuthors(const TAuthorInfoList &list)
{
    B_D(TAuthorListWidget);
    d->tbtnAdd->menu()->clear();
    d->availableAuthors = list;
    bRemoveDuplicates(d->availableAuthors);
    foreach (const TAuthorInfo &a, d->availableAuthors) {
        if (!a.isValid())
            continue;
        QAction *act = d->tbtnAdd->menu()->addAction(a.fullName());
        act->setData(a);
        bSetMapping(d->mapper, act, SIGNAL(triggered()), d->tbtnAdd->menu()->actions().count() - 1);
    }
    d->tbtnAdd->menu()->setEnabled(!d->readOnly && !d->tbtnAdd->menu()->isEmpty());
}

void TAuthorListWidget::setButtonsVisible(bool b)
{
    B_D(TAuthorListWidget);
    d->tbtnAdd->setVisible(b);
    d->tbtnRemove->setVisible(b);
    d->tbtnClear->setVisible(b);
    d->tbtnUp->setVisible(b);
    d->tbtnDown->setVisible(b);
}

void TAuthorListWidget::setAuthors(const TAuthorInfoList &list)
{
    B_D(TAuthorListWidget);
    d->lstwgt->clear();
    TAuthorInfoList nlist = list;
    bRemoveDuplicates(nlist);
    foreach (const TAuthorInfo &a, nlist) {
        if (!a.isValid())
            continue;
        d->addItem(a);
    }
}

void TAuthorListWidget::setReadOnly(bool ro)
{
    B_D(TAuthorListWidget);
    d->readOnly = ro;
    d->tbtnAdd->setEnabled(!ro);
    d->tbtnAdd->menu()->setEnabled(!ro && !d->tbtnAdd->menu()->isEmpty());
    d->lstwgtCurrentItemChanged(d->lstwgt->currentItem());
}
