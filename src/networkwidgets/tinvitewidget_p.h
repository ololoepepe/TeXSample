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

#ifndef TINVITEWIDGET_P_H
#define TINVITEWIDGET_P_H

class TInviteModel;
class TNetworkClient;

class BPasswordWidget;

class QAction;
class QItemSelection;
class QModelIndex;
class QTableView;
class QVariant;

#include "tinvitewidget.h"

#include <BeQtCore/private/bbaseobject_p.h>

#include <QSortFilterProxyModel>

/*============================================================================
================================ TInviteProxyModel ===========================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TInviteProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TInviteProxyModel(QObject *parent);
public:
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

/*============================================================================
================================ TInviteWidgetPrivate ========================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TInviteWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TInviteWidget)
public:
    TInviteModel * const Model;
public:
    QAction *actCopy;
    QAction *actDelete;
    QAction *actGenerate;
    TNetworkClient *client;
    quint16 maxInviteCount;
    TInviteProxyModel *proxyModel;
    QTableView *view;
public:
    explicit TInviteWidgetPrivate(TInviteWidget *q, TInviteModel *model);
    ~TInviteWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void clientAthorizedChanged(bool authorized);
    void copyInvites();
    void deleteInvites();
    void generateInvites();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    Q_DISABLE_COPY(TInviteWidgetPrivate)
};

#endif // TINVITEWIDGET_H
