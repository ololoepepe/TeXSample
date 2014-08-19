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

#include "tabstractlistwidgetitemdelegate.h"

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>

#include <QAbstractItemDelegate>
#include <QAction>
#include <QDebug>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QModelIndex>
#include <QObject>
#include <QPointer>
#include <QSize>
#include <QString>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QToolButton>
#include <QVariant>
#include <QVariantList>
#include <QWidget>

/*============================================================================
================================ TListWidgetProxyItemDelegate ================
============================================================================*/

/*============================== Public constructors =======================*/

TListWidgetProxyItemDelegate::TListWidgetProxyItemDelegate(TAbstractListWidgetItemDelegate *delegate,
                                                           TListWidgetPrivate *parent) :
    QStyledItemDelegate(parent), ItemDelegate(delegate)
{
    currentEditor = 0;
    currentRow = -1;
    if (!delegate)
        return;
    if (!delegate->parent())
        delegate->setParent(this);
    connect(delegate, SIGNAL(closeEditor(QWidget *)), this, SIGNAL(closeEditor(QWidget *)));
    connect(delegate, SIGNAL(closeEditor(QWidget *, QAbstractItemDelegate::EndEditHint)),
            this, SIGNAL(closeEditor(QWidget *, QAbstractItemDelegate::EndEditHint)));
    connect(delegate, SIGNAL(commitData(QWidget *)), this, SIGNAL(commitData(QWidget *)));
    connect(delegate, SIGNAL(commitDataAndCloseEditor(QWidget *)), this, SLOT(commitDataAndCloseEditor(QWidget *)));
    connect(delegate, SIGNAL(commitDataAndCloseEditor(QWidget *, QAbstractItemDelegate::EndEditHint)),
            this, SLOT(commitDataAndCloseEditor(QWidget *, QAbstractItemDelegate::EndEditHint)));
}

TListWidgetProxyItemDelegate::~TListWidgetProxyItemDelegate()
{
    //
}

/*============================== Public methods ============================*/

QWidget *TListWidgetProxyItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                                    const QModelIndex &index) const
{
    if (!ItemDelegate || !index.isValid())
        return QStyledItemDelegate::createEditor(parent, option, index);
    *const_cast<int *>(&currentRow) = index.row();
    *const_cast<QPointer<QWidget> *>(&currentEditor) = ItemDelegate->createEditor(parent, option);
    connect(currentEditor, SIGNAL(destroyed()), this, SLOT(clearCurrent()));
    return currentEditor;
}

bool TListWidgetProxyItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                               const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (!ItemDelegate || !index.isValid() || index.row() != currentRow)
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    return ItemDelegate->editorEvent(currentEditor, event, option);
}

QSize TListWidgetProxyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!ItemDelegate || !index.isValid() || currentEditor.isNull() || index.row() != currentRow)
        return QStyledItemDelegate::sizeHint(option, index);
    return ItemDelegate->sizeHint(currentEditor, option);
}

void TListWidgetProxyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!ItemDelegate || !index.isValid() || index.row() != currentRow)
        return QStyledItemDelegate::setEditorData(editor, index);
    ItemDelegate->setEditorData(editor, index.data().toString(), index.data(Qt::UserRole));
}

void TListWidgetProxyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                const QModelIndex &index) const
{
    if (!ItemDelegate || !index.isValid() || !model || index.row() != currentRow)
        return QStyledItemDelegate::setModelData(editor, model, index);
    QString text;
    QVariant data;
    if (!ItemDelegate->setModelData(editor, text, data))
        return;
    model->setData(index, text);
    model->setData(index, data, Qt::UserRole);
}

/*============================== Public slots ==============================*/

void TListWidgetProxyItemDelegate::clearCurrent()
{
    currentRow = -1;
}

void TListWidgetProxyItemDelegate::commitDataAndCloseEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    Q_EMIT commitData(editor);
    Q_EMIT closeEditor(editor, hint);
}

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

bool TListWidgetPrivate::defaultTestItemEquality(const TListWidget::Item &item1, const TListWidget::Item &item2)
{
    return item1.text == item2.text;
}

/*============================== Public methods ============================*/

void TListWidgetPrivate::init()
{
    testItemEqualityFunction = &defaultTestItemEquality;
    itemDelegate = 0;
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
    if (act)
        data = act->data();
    if (text.isEmpty()) {
        QListWidgetItem *lwi = lstwgt->item(lstwgt->count() - 1);
        if (lwi && lwi->text().isEmpty())
            return;
    }
    if (!text.isEmpty()) {
        TListWidget::Item it;
        it.text = text;
        it.data = data;
        foreach (const TListWidget::Item &itt, q_func()->items()) {
            if (testItemEqualityFunction(itt, it))
                return;
        }
        return;
    }
    QListWidgetItem *lwi = new QListWidgetItem(text);
    if (!readOnly)
        lwi->setFlags(lwi->flags () | Qt::ItemIsEditable);
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

QVariantList TListWidget::availableItemDataList() const
{
    QVariantList list;
    foreach (QAction *act, d_func()->tbtnAdd->menu()->actions())
        list << act->data();
    return list;
}

QList<TListWidget::Item> TListWidget::availableItems() const
{
    QList<Item> list = items();
    foreach (QAction *act, d_func()->tbtnAdd->menu()->actions()) {
        Item it;
        it.data = act->data();
        it.text = act->text();
        list << it;
    }
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        if (list.at(i).text.isEmpty())
            list.removeAt(i);
        foreach (int j, bRangeD(0, list.size() - 1)) {
            if (j == i)
                continue;
            if (d_func()->testItemEqualityFunction(list.at(i), list.at(j))) {
                list.removeAt(i);
                break;
            }
        }
    }
    while (d_func()->maxCount && list.size() > d_func()->maxCount)
        list.removeFirst();
    return list;
}

QStringList TListWidget::availableItemTexts() const
{
    QStringList list = itemTexts();
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

QVariantList TListWidget::itemDataList() const
{
    QVariantList list;
    foreach (int i, bRangeD(0, d_func()->lstwgt->count() - 1)) {
        if (d_func()->lstwgt->item(i)->text().isEmpty())
            continue;
        list << d_func()->lstwgt->item(i)->data(Qt::UserRole);
    }
    return list;
}

TAbstractListWidgetItemDelegate *TListWidget::itemDelegate() const
{
    return d_func()->itemDelegate ? d_func()->itemDelegate->ItemDelegate : 0;
}

QList<TListWidget::Item> TListWidget::items() const
{
    QList<Item> list;
    foreach (int i, bRangeD(0, d_func()->lstwgt->count() - 1)) {
        Item it;
        it.text = d_func()->lstwgt->item(i)->text();
        it.data = d_func()->lstwgt->item(i)->data(Qt::UserRole);
        list << it;
    }
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        if (list.at(i).text.isEmpty())
            list.removeAt(i);
        foreach (int j, bRangeD(0, list.size() - 1)) {
            if (j == i)
                continue;
            if (d_func()->testItemEqualityFunction(list.at(i), list.at(j))) {
                list.removeAt(i);
                break;
            }
        }
    }
    while (d_func()->maxCount && list.size() > d_func()->maxCount)
        list.removeFirst();
    return list;
}

QString TListWidget::itemText(int index) const
{
    if (index < 0 || index >= d_func()->lstwgt->count())
        return QString();
    return d_func()->lstwgt->item(index)->text();
}

QStringList TListWidget::itemTexts() const
{
    QStringList list;
    foreach (int i, bRangeD(0, d_func()->lstwgt->count() - 1))
        list << d_func()->lstwgt->item(i)->text();
    list.removeAll("");
    list.removeDuplicates();
    return list;
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
    B_D(TListWidget);
    bRemoveDuplicates(list, d->testItemEqualityFunction);
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        if (list.at(i).text.isEmpty())
            list.removeAt(i);
    }
    d->tbtnAdd->menu()->clear();
    while (d->maxCount && list.size() > d->maxCount)
        list.removeFirst();
    foreach (const Item &item, list) {
        QAction *act = d->tbtnAdd->menu()->addAction(item.text);
        act->setData(item.data);
        connect(act, SIGNAL(triggered()), d, SLOT(addItem()));
    }
    d->tbtnAdd->setEnabled(!d->tbtnAdd->menu()->isEmpty());
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

void TListWidget::setItemDelegate(TAbstractListWidgetItemDelegate *delegate)
{
    B_D(TListWidget);
    if (d->itemDelegate)
        d->lstwgt->setItemDelegate(0);
    delete d->itemDelegate;
    d->itemDelegate = 0;
    if (delegate) {
        d->itemDelegate = new TListWidgetProxyItemDelegate(delegate, d);
        d->lstwgt->setItemDelegate(d->itemDelegate);
    }
}

void TListWidget::setItems(QList<Item> list)
{
    B_D(TListWidget);
    bRemoveDuplicates(list, d->testItemEqualityFunction);
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        if (list.at(i).text.isEmpty())
            list.removeAt(i);
    }
    d->lstwgt->clear();
    d->lstwgtCurrentItemChanged(d->lstwgt->currentItem());
    foreach (const Item &item, list)
        d->addItem(item.text, item.data);
    if (!isReadOnly())
        d->addItem();
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

void TListWidget::setTestItemEqualityFunction(TestItemEqualityFunction f)
{
    d_func()->testItemEqualityFunction = f ? f : &TListWidgetPrivate::defaultTestItemEquality;
}

TListWidget::TestItemEqualityFunction TListWidget::testItemEqualityFunction() const
{
    return d_func()->testItemEqualityFunction;
}
