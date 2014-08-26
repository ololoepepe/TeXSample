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

#include <QAbstractTableModel>
#include <QDateTime>
#include <QDebug>
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
    QDateTime lastUpdateDateTime;
    QMap<quint64, TGroupInfo *> map;
public:
    explicit TGroupModelPrivate(TGroupModel *q);
    ~TGroupModelPrivate();
public:
    int indexOf(quint64 id) const;
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

int TGroupModelPrivate::indexOf(quint64 id) const
{
    if (!id)
        return -1;
    foreach (int i, bRangeD(0, groups.size() - 1)) {
        if (groups.at(i).id() == id)
            return i;
    }
    return -1;
}

void TGroupModelPrivate::init()
{
    lastUpdateDateTime.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TGroupModel =================================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupModel::TGroupModel(QObject *parent) :
    QAbstractTableModel(parent), BBase(*new TGroupModelPrivate(this))
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
        if (d->map.contains(info.id())) {
            if (info.lastModificationDateTime() > d->map.value(info.id())->lastModificationDateTime()) {
                int row = d->indexOf(info.id());
                d->groups[row] = info;
                d->map.insert(info.id(), &d->groups[row]);
                Q_EMIT dataChanged(index(row, 0), index(row, columnCount() - 1));
            }
            list.removeAt(i);
        } else if (!info.isValid()) {
            list.removeAt(i);
        }
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
    return 6;
}

QVariant TGroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.column() > 5 || Qt::DisplayRole != role)
        return QVariant();
    TGroupInfo info = groupInfoAt(index.row());
    if (!info.isValid())
        return QVariant();
    switch (index.column()) {
    case 0:
        return info.id();
    case 1:
        return info.name();
    case 2:
        return info.ownerId();
    case 3:
        return info.ownerLogin();
    case 4:
        return info.creationDateTime();
    case 5:
        return info.lastModificationDateTime();
    default:
        return QVariant();
    }
}

TGroupInfo TGroupModel::groupInfo(quint64 id) const
{
    const TGroupInfo *info = id ? d_func()->map.value(id) : 0;
    return info ? *info : TGroupInfo();
}

TGroupInfo TGroupModel::groupInfoAt(int index) const
{
    return (index >= 0 && index < d_func()->groups.size()) ? d_func()->groups.at(index) : TGroupInfo();
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
    case 2:
        return tr("Owner ID", "headerData");
    case 3:
        return tr("Owner login", "headerData");
    case 4:
        return tr("Creation date", "headerData");
    case 5:
        return tr("Last modified", "headerData");
    default:
        return QVariant();
    }
}

QDateTime TGroupModel::lastUpdateDateTime() const
{
    return d_func()->lastUpdateDateTime;
}

void TGroupModel::removeGroup(quint64 id)
{
    if (!id || !d_func()->map.contains(id))
        return;
    d_func()->map.remove(id);
    int ind = d_func()->indexOf(id);
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

void TGroupModel::update(const TGroupInfoList &newGroups, const TIdList &deletedGroups,
                         const QDateTime &updateDateTime)
{
    removeGroups(deletedGroups);
    addGroups(newGroups);
    d_func()->lastUpdateDateTime = updateDateTime.toUTC();
}

void TGroupModel::update(const TGroupInfoList &newGroups, const QDateTime &updateDateTime)
{
    update(newGroups, TIdList(), updateDateTime);
}

void TGroupModel::updateGroup(quint64 groupId, const TGroupInfo &newInfo)
{
    if (!groupId)
        return;
    TGroupInfo *info = d_func()->map.value(groupId);
    if (!info)
        return;
    int row = d_func()->indexOf(groupId);
    *info = newInfo;
    emit dataChanged(index(row, 0), index(row, 5));
}
