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

#include "tidlist.h"
#include "tinviteinfo.h"
#include "tinviteinfolist.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>
#include <BUuid>

#include <QAbstractListModel>
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
    QMap<quint64, TInviteInfo *> map;
public:
    explicit TInviteModelPrivate(TInviteModel *q);
    ~TInviteModelPrivate();
public:
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

void TInviteModelPrivate::init()
{
    //
}

/*============================================================================
================================ TInviteModel ================================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteModel::TInviteModel(QObject *parent) :
    QAbstractListModel(parent), BBase(*new TInviteModelPrivate(this))
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
        if (!info.isValid())
            list.removeAt(i);
        else if (d->map.contains(info.id()))
            removeInvite(info.id());
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
    return 2;
}

QVariant TInviteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (Qt::DisplayRole != role && Qt::ToolTipRole != role) || index.column() > 1)
        return QVariant();
    const TInviteInfo *info = inviteInfoAt(index.row());
    if (!info)
        return QVariant();
    if (Qt::ToolTipRole == role)
        return BeQt::pureUuidText(info->code()) + " [" + info->ownerLogin() + "]";
    switch (index.column()) {
    case 0:
        return info->id();
    case 1:
        return info->expirationDateTime().toString("dd MMMM yyyy hh:mm");
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
        return tr("Expiration date", "headerData");
    default:
        return QVariant();
    }
}

const TInviteInfo* TInviteModel::inviteInfo(quint64 id) const
{
    return id ? d_func()->map.value(id) : 0;
}

const TInviteInfo* TInviteModel::inviteInfoAt(int index) const
{
    return (index >= 0 && index < d_func()->invites.size()) ? &d_func()->invites.at(index) : 0;
}

void TInviteModel::removeInvite(quint64 id)
{
    if (!id || !d_func()->map.contains(id))
        return;
    TInviteInfo *info = d_func()->map.take(id);
    int ind = d_func()->invites.indexOf(*info);
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
