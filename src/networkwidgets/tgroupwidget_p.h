/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleNetworkWidgets module
** of the TeXSample library.
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

#ifndef TGROUPWIDGET_P_H
#define TGROUPWIDGET_P_H

class TAbstractCache;
class TGroupModel;
class TNetworkClient;

class BPasswordWidget;

class QAction;
class QItemSelection;
class QTableView;
class QVariant;

#include "tgroupwidget.h"

#include <BeQtCore/private/bbaseobject_p.h>

#include <QModelIndex>
#include <QSortFilterProxyModel>

/*============================================================================
================================ TGroupProxyModel ============================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TGroupProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TGroupProxyModel(QObject *parent);
public:
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

/*============================================================================
================================ TGroupWidgetPrivate =========================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TGroupWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TGroupWidget)
public:
    TGroupModel * const Model;
public:
    QAction *actAdd;
    QAction *actDelete;
    QAction *actEdit;
    TAbstractCache *cache;
    TNetworkClient *client;
    TGroupProxyModel *proxyModel;
    QTableView *view;
public:
    explicit TGroupWidgetPrivate(TGroupWidget *q, TGroupModel *model);
    ~TGroupWidgetPrivate();
public:
    void init();
    void updateGroupList();
public Q_SLOTS:
    void addGroup();
    void clientAuthorizedChanged(bool authorized);
    void deleteGroup();
    void editGroup(QModelIndex index = QModelIndex());
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    Q_DISABLE_COPY(TGroupWidgetPrivate)
};

#endif // TGROUPWIDGET_H
