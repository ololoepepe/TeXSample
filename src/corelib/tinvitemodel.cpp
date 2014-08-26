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

#include "tinvitemodel.h"

#include "taccesslevel.h"
#include "tgroupinfolist.h"
#include "tidlist.h"
#include "tinviteinfo.h"
#include "tinviteinfolist.h"
#include "tservicelist.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QAbstractTableModel>
#include <QDateTime>
#include <QMap>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QVariant>

/*============================================================================
================================ TInviteModelPrivate =========================
============================================================================*/

class TInviteModelPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TInviteModel)
public:
    TInviteInfoList invites;
    QDateTime lastUpdateDateTime;
    QMap<quint64, TInviteInfo *> map;
public:
    explicit TInviteModelPrivate(TInviteModel *q);
    ~TInviteModelPrivate();
public:
    int indexOf(quint64 id) const;
    void init();
private:
    Q_DISABLE_COPY(TInviteModelPrivate)
};

/*============================================================================
================================ TInviteModelPrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteModelPrivate::TInviteModelPrivate(TInviteModel *q) :
    BBasePrivate(q)
{
    //
}

TInviteModelPrivate::~TInviteModelPrivate()
{
    //
}

/*============================== Public methods ============================*/

int TInviteModelPrivate::indexOf(quint64 id) const
{
    if (!id)
        return -1;
    foreach (int i, bRangeD(0, invites.size() - 1)) {
        if (invites.at(i).id() == id)
            return i;
    }
    return -1;
}

void TInviteModelPrivate::init()
{
    //
}

/*============================================================================
================================ TInviteModel ================================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteModel::TInviteModel(QObject *parent) :
    QAbstractTableModel(parent), BBase(*new TInviteModelPrivate(this))
{
    d_func()->init();
}

TInviteModel::~TInviteModel()
{
    //
}

/*============================== Public methods ============================*/

void TInviteModel::addInvite(const TInviteInfo &invite)
{
    TInviteInfoList list;
    list << invite;
    addInvites(list);
}

void TInviteModel::addInvites(const TInviteInfoList &inviteList)
{
    B_D(TInviteModel);
    TInviteInfoList list = inviteList;
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        const TInviteInfo &info = list.at(i);
        if (d->map.contains(info.id())) {
            int row = d->indexOf(info.id());
            d->invites[row] = info;
            d->map.insert(info.id(), &d->invites[row]);
            Q_EMIT dataChanged(index(row, 0), index(row, columnCount() - 1));
            list.removeAt(i);
        } else if (!info.isValid()) {
            list.removeAt(i);
        }
    }
    if (list.isEmpty())
        return;
    int ind = d->invites.size();
    beginInsertRows(QModelIndex(), ind, ind + list.size() - 1);
    foreach (const TInviteInfo &info, list) {
        d->invites.append(info);
        d->map.insert(info.id(), &d->invites.last());
    }
    endInsertRows();
}

int TInviteModel::columnCount(const QModelIndex &) const
{
    return 9;
}

QVariant TInviteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.column() > 8 || Qt::DisplayRole != role)
        return QVariant();
    TInviteInfo info = inviteInfoAt(index.row());
    if (!info.isValid())
        return QVariant();
    switch (index.column()) {
    case 0:
        return info.id();
    case 1:
        return info.code();
    case 2:
        return info.accessLevel();
    case 3:
        return info.services();
    case 4:
        return info.groups();
    case 5:
        return info.ownerId();
    case 6:
        return info.ownerLogin();
    case 7:
        return info.creationDateTime();
    case 8:
        return info.expirationDateTime();
    default:
        return QVariant();
    }
}

QVariant TInviteModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::Horizontal != orientation || Qt::DisplayRole != role)
        return QVariant();
    switch (section) {
    case 0:
        return tr("ID", "headerData");
    case 1:
        return tr("Code", "headerData");
    case 2:
        return tr("Access level", "headerData");
    case 3:
        return tr("Services", "headerData");
    case 4:
        return tr("Groups", "headerData");
    case 5:
        return tr("Owner ID", "headerData");
    case 6:
        return tr("Owner login", "headerData");
    case 7:
        return tr("Creation date", "headerData");
    case 8:
        return tr("Expiration date", "headerData");
    default:
        return QVariant();
    }
}

TInviteInfo TInviteModel::inviteInfo(quint64 id) const
{
    const TInviteInfo *info = id ? d_func()->map.value(id) : 0;
    return info ? *info : TInviteInfo();
}

TInviteInfo TInviteModel::inviteInfoAt(int index) const
{
    return (index >= 0 && index < d_func()->invites.size()) ? d_func()->invites.at(index) : TInviteInfo();
}

QDateTime TInviteModel::lastUpdateDateTime() const
{
    return d_func()->lastUpdateDateTime;
}

void TInviteModel::removeInvite(quint64 id)
{
    if (!id || !d_func()->map.contains(id))
        return;
    d_func()->map.remove(id);
    int ind = d_func()->indexOf(id);
    beginRemoveRows(QModelIndex(), ind, ind);
    d_func()->invites.removeAt(ind);
    endRemoveRows();
}

void TInviteModel::removeInvites(const TIdList &idList)
{
    foreach (quint64 id, idList)
        removeInvite(id);
}

int TInviteModel::rowCount(const QModelIndex &) const
{
    return d_func()->invites.size();
}

void TInviteModel::update(const TInviteInfoList &newInvites, const TIdList &deletedInvites,
                          const QDateTime &updateDateTime)
{
    removeInvites(deletedInvites);
    addInvites(newInvites);
    d_func()->lastUpdateDateTime = updateDateTime.toUTC();
}

void TInviteModel::update(const TInviteInfoList &newInvites, const QDateTime &updateDateTime)
{
    update(newInvites, TIdList(), updateDateTime);
}
