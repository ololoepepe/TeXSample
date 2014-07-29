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

#ifndef TGROUPWIDGET_H
#define TGROUPWIDGET_H

class TGroupWidgetPrivate;

class TAddGroupRequestData;
class TDeleteGroupRequestData;
class TEditGroupRequestData;
class TGroupModel;
class TReply;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TGroupWidget ================================
============================================================================*/

class T_WIDGETS_EXPORT TGroupWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TGroupWidget)
public:
    typedef TReply (*AddGroupFunction)(const TAddGroupRequestData &data, QWidget *parent);
    typedef TReply (*DeleteGroupFunction)(const TDeleteGroupRequestData &data, QWidget *parent);
    typedef TReply (*EditGroupFunction)(const TEditGroupRequestData &data, QWidget *parent);
public:
    explicit TGroupWidget(TGroupModel *model, QWidget *parent = 0);
    ~TGroupWidget();
public:
    AddGroupFunction addGroupFunction() const;
    DeleteGroupFunction deleteGroupFunction() const;
    EditGroupFunction editGroupFunction() const;
    void setAddGroupFunction(AddGroupFunction addGroupFunction);
    void setDeleteGroupFunction(DeleteGroupFunction deleteGroupFunction);
    void setEditGroupFunction(EditGroupFunction editGroupFunction);
private:
    Q_DISABLE_COPY(TGroupWidget)
};

#endif // TGROUPWIDGET_H
