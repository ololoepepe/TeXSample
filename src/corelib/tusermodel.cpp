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

#include "tusermodel.h"

#include "taccesslevel.h"
#include "tidlist.h"
#include "tuserinfo.h"
#include "tuserinfolist.h"

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
================================ TUserModelPrivate ===========================
============================================================================*/

class TUserModelPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TUserModel)
public:
    TUserInfoList users;
    QMap<quint64, TUserInfo *> map;
public:
    explicit TUserModelPrivate(TUserModel *q);
    ~TUserModelPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TUserModelPrivate)
};

/*============================================================================
================================ TUserModelPrivate ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TUserModelPrivate::TUserModelPrivate(TUserModel *q) :
    BBasePrivate(q)
{
    //
}

TUserModelPrivate::~TUserModelPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserModelPrivate::init()
{
    //
}

/*============================================================================
================================ TUserModel ==================================
============================================================================*/

/*============================== Public constructors =======================*/

TUserModel::TUserModel(QObject *parent) :
    QAbstractListModel(parent), BBase(*new TUserModelPrivate(this))
{
    d_func()->init();
}

TUserModel::~TUserModel()
{
    //
}

/*============================== Public methods ============================*/

void TUserModel::addUser(const TUserInfo &user)
{
    TUserInfoList list;
    list << user;
    addUsers(list);
}

void TUserModel::addUsers(const TUserInfoList &userList)
{
    B_D(TUserModel);
    TUserInfoList list = userList;
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        const TUserInfo &info = list.at(i);
        if (!info.isValid())
            list.removeAt(i);
        else if (d->map.contains(info.id()))
            removeUser(info.id());
    }
    if (list.isEmpty())
        return;
    int ind = d->users.size();
    beginInsertRows(QModelIndex(), ind, ind + list.size() - 1);
    foreach (const TUserInfo &info, list) {
        d->users.append(info);
        d->map.insert(info.id(), &d->users.last());
    }
    endInsertRows();
}

int TUserModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant TUserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (Qt::DisplayRole != role && Qt::ToolTipRole != role) || index.column() > 2)
        return QVariant();
    const TUserInfo *info = userInfoAt(index.row());
    if (!info)
        return QVariant();
    if (Qt::ToolTipRole == role)
        return info->accessLevel().toString() + ", "
                + (info->active() ? tr("active", "data") : tr("inactive", "data"));
    switch (index.column()) {
    case 0:
        return info->id();
    case 1:
        return info->login();
    case 2:
        return info->name() + (!info->patronymic().isEmpty() ? (" " + info->patronymic()) : QString())
                + (!info->surname().isEmpty() ? (" " + info->surname()) : QString());
    default:
        return QVariant();
    }
}

QVariant TUserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::Horizontal != orientation || Qt::DisplayRole != role)
        return QVariant();
    switch (section) {
    case 0:
        return tr("ID", "headerData");
    case 1:
        return tr("Login", "headerData");
    case 2:
        return tr("Name", "headerData");
    default:
        return QVariant();
    }
}

const TUserInfo* TUserModel::userInfo(quint64 id) const
{
    return id ? d_func()->map.value(id) : 0;
}

const TUserInfo* TUserModel::userInfoAt(int index) const
{
    return (index >= 0 && index < d_func()->users.size()) ? &d_func()->users.at(index) : 0;
}

void TUserModel::removeUser(quint64 id)
{
    if (!id || !d_func()->map.contains(id))
        return;
    TUserInfo *info = d_func()->map.take(id);
    int ind = d_func()->users.indexOf(*info);
    beginRemoveRows(QModelIndex(), ind, ind);
    d_func()->users.removeAt(ind);
    endRemoveRows();
}

void TUserModel::removeUsers(const TIdList &idList)
{
    foreach (quint64 id, idList)
        removeUser(id);
}

int TUserModel::rowCount(const QModelIndex &) const
{
    return d_func()->users.size();
}
