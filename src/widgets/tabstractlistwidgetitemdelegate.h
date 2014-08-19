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

#ifndef TABSTRACTLISTWIDGETITEMDELEGATE_H
#define TABSTRACTLISTWIDGETITEMDELEGATE_H

class QEvent;
class QSize;
class QString;
class QStyleOptionViewItem;
class QVariant;
class QWidget;

#include <TeXSampleCore/TeXSampleGlobal>

#include <QAbstractItemDelegate>
#include <QObject>

/*============================================================================
================================ TAbstractListWidgetItemDelegate =============
============================================================================*/

class T_WIDGETS_EXPORT TAbstractListWidgetItemDelegate : public QObject
{
    Q_OBJECT
public:
    explicit TAbstractListWidgetItemDelegate(QObject *parent = 0);
    virtual ~TAbstractListWidgetItemDelegate();
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option) const = 0;
    virtual bool editorEvent(QWidget *editor, QEvent *event, const QStyleOptionViewItem &option);
    virtual QSize sizeHint(QWidget *editor, const QStyleOptionViewItem &option) const;
    virtual void setEditorData(QWidget *editor, const QString &text, const QVariant &data) const = 0;
    virtual bool setModelData(QWidget *editor, QString &text, QVariant &data) const = 0;
signals:
    void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint);
    void commitData(QWidget *editor);
    void commitDataAndCloseEditor(QWidget *editor,
                                  QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint);
private:
    Q_DISABLE_COPY(TAbstractListWidgetItemDelegate)
};

#endif // TABSTRACTLISTWIDGETITEMDELEGATE_H

