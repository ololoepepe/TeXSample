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

#ifndef TAUTHORINFOLISTWIDGETITEMDELEGATE_H
#define TAUTHORINFOLISTWIDGETITEMDELEGATE_H

class TAuthorInfoListWidgetItemDelegatePrivate;

class QSize;
class QString;
class QStyleOptionViewItem;
class QVariant;
class QWidget;

#include "tabstractlistwidgetitemdelegate.h"
#include "tlistwidget.h"

#include <BBaseObject>

#include <QObject>

/*============================================================================
================================ TAuthorInfoListWidgetItemDelegate ===========
============================================================================*/

class T_WIDGETS_EXPORT TAuthorInfoListWidgetItemDelegate : public TAbstractListWidgetItemDelegate, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TAuthorInfoListWidgetItemDelegate)
public:
    explicit TAuthorInfoListWidgetItemDelegate(QObject *parent = 0);
    virtual ~TAuthorInfoListWidgetItemDelegate();
public:
    static bool testItemEquality(const TListWidget::Item &item1, const TListWidget::Item &item2);
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option) const;
    QSize sizeHint(QWidget *editor, const QStyleOptionViewItem &option) const;
    void setEditorData(QWidget *editor, const QString &text, const QVariant &data) const;
    bool setModelData(QWidget *editor, QString &text, QVariant &data) const;
private:
    Q_DISABLE_COPY(TAuthorInfoListWidgetItemDelegate)
};

#endif // TAUTHORINFOLISTWIDGETITEMDELEGATE_H

