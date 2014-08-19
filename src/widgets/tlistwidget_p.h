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

#ifndef TLISTWIDGET_P_H
#define TLISTWIDGET_P_H

class TAbstractListWidgetItemDelegate;

class QListWidget;
class QListWidgetItem;
class QModelIndex;
class QStyleOptionViewItem;
class QToolButton;

#include "tlistwidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>
#include <QString>
#include <QStyledItemDelegate>
#include <QVariant>

/*============================================================================
================================ TListWidgetProxyItemDelegate ================
============================================================================*/

class T_WIDGETS_EXPORT TListWidgetProxyItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TAbstractListWidgetItemDelegate * const ItemDelegate;
public:
    explicit TListWidgetProxyItemDelegate(TAbstractListWidgetItemDelegate *delegate, QObject *parent = 0);
    ~TListWidgetProxyItemDelegate();
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

/*============================================================================
================================ TListWidgetPrivate ==========================
============================================================================*/

class T_WIDGETS_EXPORT TListWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TListWidget)
public:
    TListWidgetProxyItemDelegate *itemDelegate;
    QListWidget *lstwgt;
    int maxCount;
    bool readOnly;
    QToolButton *tbtnAdd;
    QToolButton *tbtnClear;
    QToolButton *tbtnDown;
    QToolButton *tbtnRemove;
    QToolButton *tbtnUp;
public:
    explicit TListWidgetPrivate(TListWidget *q);
    ~TListWidgetPrivate();
public:
    static bool itemsEqual(const TListWidget::Item &item1, const TListWidget::Item &item2);
public:
    void init();
public Q_SLOTS:
    void addItem(QString text = QString(), QVariant data = QVariant());
    void clearList();
    void lstwgtCurrentItemChanged(QListWidgetItem *current);
    void moveItemDown();
    void moveItemUp();
    void removeSelectedItem();
private:
    Q_DISABLE_COPY(TListWidgetPrivate)
};

#endif // TLISTWIDGET_P_H

