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

#ifndef TAUTHORINFOLISTWIDGETITEMDELEGATE_P_H
#define TAUTHORINFOLISTWIDGETITEMDELEGATE_P_H

class TAuthorInfoWidget;

class QEvent;
class QPushButton;

#include "tauthorinfolistwidgetitemdelegate.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>

/*============================================================================
================================ TAuthorInfoDelegateWidget ===================
============================================================================*/

class TAuthorInfoDelegateWidget : public QWidget
{
    Q_OBJECT
private:
    TAuthorInfoWidget *mauthorInfoWidget;
    QPushButton *btnAccept;
    QPushButton *btnReject;
public:
    explicit TAuthorInfoDelegateWidget(QWidget *parent = 0);
public:
    TAuthorInfoWidget *authorInfoWidget();
    bool eventFilter(QObject *object, QEvent *event);
public Q_SLOTS:
    void accepted();
    void rejected();
Q_SIGNALS:
    void closeEditor(QWidget *editor);
    void commitDataAndCloseEditor(QWidget *editor);
};

/*============================================================================
================================ TAuthorInfoListWidgetItemDelegatePrivate ====
============================================================================*/

class T_WIDGETS_EXPORT TAuthorInfoListWidgetItemDelegatePrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TAuthorInfoListWidgetItemDelegate)
public:
    bool isAccepted;
public:
    explicit TAuthorInfoListWidgetItemDelegatePrivate(TAuthorInfoListWidgetItemDelegate *q);
    ~TAuthorInfoListWidgetItemDelegatePrivate();
public:
    void init();
public Q_SLOTS:
    void clearCurrent();
    void commitDataAndCloseEditor(QWidget *editor);
private:
    Q_DISABLE_COPY(TAuthorInfoListWidgetItemDelegatePrivate)
};

#endif // TAUTHORINFOLISTWIDGETITEMDELEGATE_P_H

