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

#ifndef TLISTWIDGET_H
#define TLISTWIDGET_H

class TListWidgetPrivate;

class TAbstractListWidgetItemDelegate;

class QStringList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QList>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QWidget>

/*============================================================================
================================ TListWidget =================================
============================================================================*/

class T_WIDGETS_EXPORT TListWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TListWidget)
public:
    struct Item
    {
        QVariant data;
        QString text;
    };
public:
    typedef bool (*TestItemEqualityFunction)(const Item &, const Item &);
public:
    explicit TListWidget(QWidget *parent = 0);
    ~TListWidget();
protected:
    explicit TListWidget(TListWidgetPrivate &d, QWidget *parent = 0);
public:
    int availableItemCount() const;
    QVariant availableItemData(int index) const;
    QVariantList availableItemDataList() const;
    QList<Item> availableItems() const;
    QStringList availableItemTexts() const;
    bool buttonsVisible() const;
    void clear();
    bool isReadOnly() const;
    int itemCount() const;
    QVariant itemData(int index) const;
    QVariantList itemDataList() const;
    TAbstractListWidgetItemDelegate *itemDelegate() const;
    QList<Item> items() const;
    QString itemText(int index) const;
    QStringList itemTexts() const;
    int maxAvailableItems() const;
    void setAvailableItemData(int index, const QVariant &data);
    void setAvailableItems(QList<Item> list);
    void setAvailableItems(const QStringList &list);
    void setButtonsVisible(bool b);
    void setItemData(int index, const QVariant &data);
    void setItemDelegate(TAbstractListWidgetItemDelegate *delegate);
    void setItems(QList<Item> list);
    void setItems(const QStringList &list);
    void setMaxAvailableItems(int count);
    void setReadOnly(bool ro);
    void setTestItemEqualityFunction(TestItemEqualityFunction f);
    TestItemEqualityFunction testItemEqualityFunction() const;
private:
    Q_DISABLE_COPY(TListWidget)
};

#endif // TLISTWIDGET_H

