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

#ifndef TUSERWIDGET_P_H
#define TUSERWIDGET_P_H

class TAbstractCache;
class TNetworkClient;
class TUserModel;

class BPasswordWidget;

class QAction;
class QItemSelection;
class QTableView;
class QVariant;

#include "tuserwidget.h"

#include <BeQtCore/private/bbaseobject_p.h>

#include <QModelIndex>
#include <QSortFilterProxyModel>

/*============================================================================
================================ TUserProxyModel =============================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TUserProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TUserProxyModel(QObject *parent);
public:
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

/*============================================================================
================================ TUserWidgetPrivate ==========================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TUserWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TUserWidget)
public:
    TUserModel * const Model;
public:
    QAction *actAdd;
    QAction *actDelete;
    QAction *actEdit;
    TAbstractCache *cache;
    TNetworkClient *client;
    TUserProxyModel *proxyModel;
    QTableView *view;
public:
    explicit TUserWidgetPrivate(TUserWidget *q, TUserModel *model);
    ~TUserWidgetPrivate();
public:
    void init();
    void updateUserList();
public Q_SLOTS:
    void addUser();
    void clientAuthorizedChanged(bool authorized);
    void deleteUser();
    void editUser(QModelIndex index = QModelIndex());
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    Q_DISABLE_COPY(TUserWidgetPrivate)
};

#endif // TUSERWIDGET_P_H
