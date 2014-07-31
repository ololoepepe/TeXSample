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

#ifndef IGROUPWIDGET_H
#define IGROUPWIDGET_H

class TGroupModel;
class TNetworkClient;

class BPasswordWidget;

class QAction;
class QItemSelection;
class QModelIndex;
class QTableView;

#include "tgroupwidget.h"

#include <BeQtCore/private/bbaseobject_p.h>

/*============================================================================
================================ TGroupWidgetPrivate =========================
============================================================================*/

class T_WIDGETS_EXPORT TGroupWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TGroupWidget)
public:
    TGroupModel * const Model;
public:
    QAction *actAdd;
    QAction *actDelete;
    QAction *actEdit;
    TNetworkClient *client;
    QTableView *view;
public:
    explicit TGroupWidgetPrivate(TGroupWidget *q, TGroupModel *model);
    ~TGroupWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void addGroup();
    void clientAuthorizedChanged(bool authorized);
    void deleteGroup();
    void editGroup(const QModelIndex &index);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    Q_DISABLE_COPY(TGroupWidgetPrivate)
};

#endif // TGROUPWIDGET_H
