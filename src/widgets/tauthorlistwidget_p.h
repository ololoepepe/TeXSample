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

#ifndef TAUTHORLISTWIDGET_P_H
#define TAUTHORLISTWIDGET_P_H

class TAuthorInfo;

class QListWidget;
class QListWidgetItem;
class QSignalMapper;
class QToolButton;

#include "tauthorlistwidget.h"

#include <TeXSampleCore/TAuthorInfoList>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>
#include <QString>
#include <QWidget>

/*============================================================================
================================ TAuthorListWidgetPrivate ====================
============================================================================*/

class T_WIDGETS_EXPORT TAuthorListWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TAuthorListWidget)
public:
    TAuthorInfoList availableAuthors;
    QListWidget *lstwgt;
    QSignalMapper *mapper;
    bool readOnly;
    QToolButton *tbtnAdd;
    QToolButton *tbtnClear;
    QToolButton *tbtnDown;
    QToolButton *tbtnRemove;
    QToolButton *tbtnUp;
public:
    explicit TAuthorListWidgetPrivate(TAuthorListWidget *q);
    ~TAuthorListWidgetPrivate();
public:
    void addItem(const TAuthorInfo &info);
    void init();
    void resetItem(QListWidgetItem *item, const TAuthorInfo &info);
public Q_SLOTS:
    void addItem();
    void addItem(int index);
    void clearList();
    void editItem(QListWidgetItem *item);
    void lstwgtCurrentItemChanged(QListWidgetItem *current);
    void moveItemDown();
    void moveItemUp();
    void removeSelectedItem();
private:
    Q_DISABLE_COPY(TAuthorListWidgetPrivate)
};

#endif // TAUTHORLISTWIDGET_P_H

