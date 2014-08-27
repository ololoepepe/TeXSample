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

#ifndef TGROUPLISTWIDGET_H
#define TGROUPLISTWIDGET_H

class TGroupListWidgetPrivate;

class TGroupInfoList;
class TIdList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TGroupListWidget ============================
============================================================================*/

class T_WIDGETS_EXPORT TGroupListWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TGroupListWidget)
public:
    explicit TGroupListWidget(QWidget *parent = 0);
    ~TGroupListWidget();
protected:
    explicit TGroupListWidget(TGroupListWidgetPrivate &d, QWidget *parent = 0);
public:
    TGroupInfoList availableGroups() const;
    bool buttonsVisible() const;
    TIdList groupIds() const;
    TGroupInfoList groups() const;
    bool isReadOnly() const;
    void setAvailableGroups(const TGroupInfoList &list);
    void setButtonsVisible(bool b);
    void setGroups(const TGroupInfoList &list);
    void setGroups(const TIdList &list);
    void setReadOnly(bool ro);
private:
    Q_DISABLE_COPY(TGroupListWidget)
};

#endif // TGROUPLISTWIDGET_H

