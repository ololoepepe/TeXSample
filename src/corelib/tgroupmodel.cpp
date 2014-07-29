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

#include "tgroupmodel.h"

#include "tidlist.h"
#include "tgroupinfo.h"
#include "tgroupinfolist.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>

#include <QAbstractListModel>
#include <QMap>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QVariant>

/*============================================================================
================================ TGroupModelPrivate ==========================
============================================================================*/

class TGroupModelPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TGroupModel)
public:
    TGroupInfoList groups;
    QMap<quint64, TGroupInfo *> map;
public:
    explicit TGroupModelPrivate(TGroupModel *q);
    ~TGroupModelPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TGroupModelPrivate)
};

/*============================================================================
================================ TGroupModelPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupModelPrivate::TGroupModelPrivate(TGroupModel *q) :
    BBasePrivate(q)
{
    //
}

TGroupModelPrivate::~TGroupModelPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGroupModelPrivate::init()
{
    //
}

/*============================================================================
================================ TGroupModel =================================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupModel::TGroupModel(QObject *parent) :
    QAbstractListModel(parent), BBase(*new TGroupModelPrivate(this))
{
    d_func()->init();
}

TGroupModel::~TGroupModel()
{
    //
}

/*============================== Public methods ============================*/

void TGroupModel::addGroup(const TGroupInfo &group)
{
    TGroupInfoList list;
    list << group;
    addGroups(list);
}

void TGroupModel::addGroups(const TGroupInfoList &groupList)
{
    B_D(TGroupModel);
    TGroupInfoList list = groupList;
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        const TGroupInfo &info = list.at(i);
        if (!info.isValid())
            list.removeAt(i);
        else if (d->map.contains(info.id()))
            removeGroup(info.id());
    }
    if (list.isEmpty())
        return;
    int ind = d->groups.size();
    beginInsertRows(QModelIndex(), ind, ind + list.size() - 1);
    foreach (const TGroupInfo &info, list) {
        d->groups.append(info);
        d->map.insert(info.id(), &d->groups.last());
    }
    endInsertRows();
}

int TGroupModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant TGroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (Qt::DisplayRole != role && Qt::ToolTipRole != role) || index.column() > 1)
        return QVariant();
    const TGroupInfo *info = groupInfoAt(index.row());
    if (!info)
        return QVariant();
    if (Qt::ToolTipRole == role)
        return info->name() + " [" + info->ownerLogin() + "]";
    switch (index.column()) {
    case 0:
        return info->id();
    case 1:
        return info->name();
    default:
        return QVariant();
    }
}

QVariant TGroupModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::Horizontal != orientation || Qt::DisplayRole != role)
        return QVariant();
    switch (section) {
    case 0:
        return tr("ID", "headerData");
    case 1:
        return tr("Name", "headerData");
    default:
        return QVariant();
    }
}

const TGroupInfo* TGroupModel::groupInfo(quint64 id) const
{
    return id ? d_func()->map.value(id) : 0;
}

const TGroupInfo* TGroupModel::groupInfoAt(int index) const
{
    return (index >= 0 && index < d_func()->groups.size()) ? &d_func()->groups.at(index) : 0;
}

void TGroupModel::removeGroup(quint64 id)
{
    if (!id || !d_func()->map.contains(id))
        return;
    TGroupInfo *info = d_func()->map.take(id);
    int ind = d_func()->groups.indexOf(*info);
    beginRemoveRows(QModelIndex(), ind, ind);
    d_func()->groups.removeAt(ind);
    endRemoveRows();
}

void TGroupModel::removeGroups(const TIdList &idList)
{
    foreach (quint64 id, idList)
        removeGroup(id);
}

int TGroupModel::rowCount(const QModelIndex &) const
{
    return d_func()->groups.size();
}
