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

#ifndef TGROUPLISTWIDGET_P_H
#define TGROUPLISTWIDGET_P_H

class QListWidget;
class QListWidgetItem;
class QSignalMapper;
class QToolButton;

#include "tgrouplistwidget.h"

#include <TeXSampleCore/TGroupInfoList>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>
#include <QString>
#include <QWidget>

/*============================================================================
================================ TGroupListWidgetPrivate =====================
============================================================================*/

class T_WIDGETS_EXPORT TGroupListWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TGroupListWidget)
public:
    TGroupInfoList availableGroups;
    QListWidget *lstwgt;
    QSignalMapper *mapper;
    bool readOnly;
    QToolButton *tbtnAdd;
    QToolButton *tbtnClear;
    QToolButton *tbtnDown;
    QToolButton *tbtnRemove;
    QToolButton *tbtnUp;
public:
    explicit TGroupListWidgetPrivate(TGroupListWidget *q);
    ~TGroupListWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void addItem(int index);
    void clearList();
    void lstwgtCurrentItemChanged(QListWidgetItem *current);
    void moveItemDown();
    void moveItemUp();
    void removeSelectedItem();
private:
    Q_DISABLE_COPY(TGroupListWidgetPrivate)
};

#endif // TGROUPLISTWIDGET_P_H

