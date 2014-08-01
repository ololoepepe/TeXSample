/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleCore module of the TeXSample library.
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

#ifndef TGROUPMODEL_H
#define TGROUPMODEL_H

class TGroupModelPrivate;

class TIdList;
class TGroupInfo;
class TGroupInfoList;

class QObject;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QAbstractTableModel>
#include <QModelIndex>

/*============================================================================
================================ TGroupModel =================================
============================================================================*/

class T_CORE_EXPORT TGroupModel : public QAbstractTableModel, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TGroupModel)
public:
    explicit TGroupModel(QObject *parent = 0);
    ~TGroupModel();
public:
    virtual void addGroup(const TGroupInfo &group);
    virtual void addGroups(const TGroupInfoList &groupList);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual const TGroupInfo* groupInfo(quint64 id) const;
    virtual const TGroupInfo* groupInfoAt(int index) const;
    virtual void removeGroup(quint64 id);
    virtual void removeGroups(const TIdList &idList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual void updateGroup(quint64 groupId, const TGroupInfo &newInfo);
private:
    Q_DISABLE_COPY(TGroupModel)
};

#endif // TGROUPMODEL_H

