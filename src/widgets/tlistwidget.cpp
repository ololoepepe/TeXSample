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

#include "tlistwidget.h"
#include "tlistwidget_p.h"

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>

#include <QAction>
#include <QDebug>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QString>
#include <QStringList>
#include <QToolButton>
#include <QVariant>
#include <QWidget>

/*============================================================================
================================ TListWidgetPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TListWidgetPrivate::TListWidgetPrivate(TListWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TListWidgetPrivate::~TListWidgetPrivate()
{
    //
}

/*============================== Static public methods =====================*/

bool TListWidgetPrivate::itemsEqual(const TListWidget::Item &item1, const TListWidget::Item &item2)
{
    return item1.text == item2.text;
}

/*============================== Public methods ============================*/

void TListWidgetPrivate::init()
{
    readOnly = false;
    maxCount = 0;
    //
    QHBoxLayout *hlt = new QHBoxLayout(q_func());
      lstwgt = new QListWidget;
        lstwgt->setEditTriggers(QListWidget::EditKeyPressed | QListWidget::DoubleClicked);
        connect(lstwgt, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(addItem()));
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
            connect(tbtnUp, SIGNAL(clicked()), this, SLOT(moveItemUp()));
          hltw->addWidget(tbtnUp);
          tbtnDown = new QToolButton;
            tbtnDown->setIcon(BApplication::icon("1downarrow"));
            tbtnDown->setToolTip(tr("Move down", "tbtnt toolTip"));
            connect(tbtnDown, SIGNAL(clicked()), this, SLOT(moveItemDown()));
          hltw->addWidget(tbtnDown);
        vlt->addLayout(hltw);
      hlt->addLayout(vlt);
      //
    addItem();
    lstwgtCurrentItemChanged(lstwgt->currentItem());
}

/*============================== Public slots ==============================*/

void TListWidgetPrivate::addItem(QString text, QVariant data)
{
    QAction *act = qobject_cast<QAction *>(sender());
    if (act)
        text = act->text();
    if (text.isEmpty()) {
        QListWidgetItem *lwi = lstwgt->item(lstwgt->count() - 1);
        if (lwi && lwi->text().isEmpty())
            return;
    }
    if (!text.isEmpty() && q_func()->items().contains(text))
        return;
    QListWidgetItem *lwi = new QListWidgetItem(text);
    if (!readOnly)
        lwi->setFlags(lwi->flags () | Qt::ItemIsEditable);
    if (act)
        data = act->data();
    lwi->setData(Qt::UserRole, data);
    int ind = lstwgt->count();
    if (!text.isEmpty() && ind && lstwgt->item(ind - 1)->text().isEmpty())
        --ind;
    lstwgt->insertItem(ind, lwi);
    if (!q_func()->isReadOnly() || !text.isEmpty())
        lstwgt->setCurrentItem(lwi);
}

void TListWidgetPrivate::clearList()
{
    q_func()->clear();
}

void TListWidgetPrivate::lstwgtCurrentItemChanged(QListWidgetItem *current)
{
    QListWidgetItem *last = lstwgt->item(lstwgt->count() - 1);
    bool lastEmpty = last && last->text().isEmpty();
    tbtnRemove->setEnabled(current && (current != last || !lastEmpty));
    tbtnClear->setEnabled(lstwgt->count() > 1 || (lstwgt->count() == 1 && !lastEmpty));
    tbtnUp->setEnabled(current && current != lstwgt->item(0) && (current != last || !lastEmpty));
    tbtnDown->setEnabled(current && current != last && (!lastEmpty || current != lstwgt->item(lstwgt->count() - 2)));
}

void TListWidgetPrivate::moveItemDown()
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

void TListWidgetPrivate::moveItemUp()
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

void TListWidgetPrivate::removeSelectedItem()
{
    delete lstwgt->takeItem(lstwgt->currentRow());
    lstwgtCurrentItemChanged(lstwgt->currentItem());
}

/*============================================================================
================================ TListWidget =================================
============================================================================*/

/*============================== Public constructors =======================*/

TListWidget::TListWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TListWidgetPrivate(this))
{
    d_func()->init();
}

TListWidget::~TListWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TListWidget::TListWidget(TListWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

int TListWidget::availableItemCount() const
{
    return d_func()->tbtnAdd->menu()->actions().count();
}

QVariant TListWidget::availableItemData(int index) const
{
    if (index < 0)
        return QVariant();
    QList<QAction *> list = d_func()->tbtnAdd->menu()->actions();
    if (index >= list.size())
        return QVariant();
    return list.at(index)->data();
}

QStringList TListWidget::availableItems() const
{
    QStringList list = items();
    foreach (QAction *act, d_func()->tbtnAdd->menu()->actions())
        list << act->text();
    list.removeAll("");
    list.removeDuplicates();
    while (d_func()->maxCount && list.size() > d_func()->maxCount)
        list.removeFirst();
    return list;
}

bool TListWidget::buttonsVisible() const
{
    return d_func()->tbtnAdd->isVisible();
}

void TListWidget::clear()
{
    setItems(QStringList());
}

bool TListWidget::isReadOnly() const
{
    return d_func()->readOnly;
}

int TListWidget::itemCount() const
{
    return d_func()->lstwgt->count();
}

QVariant TListWidget::itemData(int index) const
{
    if (index < 0 || index >= d_func()->lstwgt->count())
        return QVariant();
    return d_func()->lstwgt->item(index)->data(Qt::UserRole);
}

QStringList TListWidget::items() const
{
    QStringList list;
    foreach (int i, bRangeD(0, d_func()->lstwgt->count() - 1))
        list << d_func()->lstwgt->item(i)->text();
    list.removeAll("");
    list.removeDuplicates();
    return list;
}

QString TListWidget::itemText(int index) const
{
    if (index < 0 || index >= d_func()->lstwgt->count())
        return QString();
    return d_func()->lstwgt->item(index)->text();
}

int TListWidget::maxAvailableItems() const
{
    return d_func()->maxCount;
}

void TListWidget::setAvailableItemData(int index, const QVariant &data)
{
    if (index < 0)
        return;
    QList<QAction *> list = d_func()->tbtnAdd->menu()->actions();
    if (index >= list.size())
        return;
    list.at(index)->setData(data);
}

void TListWidget::setAvailableItems(QList<Item> list)
{
    bRemoveDuplicates(list, &TListWidgetPrivate::itemsEqual);
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        if (list.at(i).text.isEmpty())
            list.removeAt(i);
    }
    d_func()->tbtnAdd->menu()->clear();
    while (d_func()->maxCount && list.size() > d_func()->maxCount)
        list.removeFirst();
    foreach (const Item &item, list) {
        QAction *act = d_func()->tbtnAdd->menu()->addAction(item.text);
        act->setData(item.data);
        connect(act, SIGNAL(triggered()), d_func(), SLOT(addItem()));
    }
    d_func()->tbtnAdd->setEnabled(!d_func()->tbtnAdd->menu()->isEmpty());
}

void TListWidget::setAvailableItems(const QStringList &list)
{
    QList<Item> items;
    foreach (const QString &text, list) {
        Item item;
        item.text = text;
        items << item;
    }
    setAvailableItems(items);
}

void TListWidget::setButtonsVisible(bool b)
{
    d_func()->tbtnAdd->setVisible(b);
    d_func()->tbtnRemove->setVisible(b);
    d_func()->tbtnClear->setVisible(b);
    d_func()->tbtnUp->setVisible(b);
    d_func()->tbtnDown->setVisible(b);
}

void TListWidget::setItemData(int index, const QVariant &data)
{
    if (index < 0 || index >= d_func()->lstwgt->count())
        return;
    d_func()->lstwgt->item(index)->setData(Qt::UserRole, data);
}

void TListWidget::setItems(QList<Item> list)
{
    bRemoveDuplicates(list, &TListWidgetPrivate::itemsEqual);
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        if (list.at(i).text.isEmpty())
            list.removeAt(i);
    }
    d_func()->lstwgt->clear();
    d_func()->lstwgtCurrentItemChanged(d_func()->lstwgt->currentItem());
    foreach (const Item &item, list)
        d_func()->addItem(item.text, item.data);
    if (!isReadOnly())
        d_func()->addItem();
}

void TListWidget::setItems(const QStringList &list)
{
    QList<Item> items;
    foreach (const QString &text, list) {
        Item item;
        item.text = text;
        items << item;
    }
    setItems(items);
}

void TListWidget::setReadOnly(bool ro)
{
    if (ro == d_func()->readOnly)
        return;
    d_func()->readOnly = ro;
    d_func()->lstwgt->setEditTriggers(ro ? QListWidget::NoEditTriggers :
                                           (QListWidget::EditKeyPressed | QListWidget::DoubleClicked));
    setItems(items());
}

void TListWidget::setMaxAvailableItems(int count)
{
    if (count < 0)
        count = 0;
    if (count == d_func()->maxCount)
        return;
    d_func()->maxCount = count;
    setAvailableItems(availableItems());
}
