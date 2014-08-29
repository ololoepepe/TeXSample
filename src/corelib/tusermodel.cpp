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
#include "tgroupinfolist.h"
#include "tidlist.h"
#include "tservicelist.h"
#include "tuserinfo.h"
#include "tuserinfolist.h"

#include <BBase>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>

#include <QAbstractTableModel>
#include <QDateTime>
#include <QImage>
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
    QDateTime lastUpdateDateTime;
    QMap<quint64, TUserInfo *> map;
    TUserInfoList users;
public:
    explicit TUserModelPrivate(TUserModel *q);
    ~TUserModelPrivate();
public:
    int indexOf(quint64 id) const;
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

int TUserModelPrivate::indexOf(quint64 id) const
{
    if (!id)
        return -1;
    foreach (int i, bRangeD(0, users.size() - 1)) {
        if (users.at(i).id() == id)
            return i;
    }
    return -1;
}

void TUserModelPrivate::init()
{
    lastUpdateDateTime.setTimeSpec(Qt::UTC);
}

/*============================================================================
================================ TUserModel ==================================
============================================================================*/

/*============================== Public constructors =======================*/

TUserModel::TUserModel(QObject *parent) :
    QAbstractTableModel(parent), BBase(*new TUserModelPrivate(this))
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
        if (d->map.contains(info.id())) {
            if (info.lastModificationDateTime() > d->map.value(info.id())->lastModificationDateTime()) {
                int row = d->indexOf(info.id());
                d->users[row] = info;
                if (avatarStoredSeparately()) {
                    saveAvatar(info.id(), info.avatar());
                    d->users[row].setAvatar(QImage());
                }
                d->map.insert(info.id(), &d->users[row]);
                Q_EMIT dataChanged(index(row, 0), index(row, columnCount() - 1));
            }
            list.removeAt(i);
        } else if (!info.isValid()) {
            list.removeAt(i);
        }
    }
    if (list.isEmpty())
        return;
    int ind = d->users.size();
    beginInsertRows(QModelIndex(), ind, ind + list.size() - 1);
    foreach (TUserInfo info, list) {
        if (avatarStoredSeparately()) {
            saveAvatar(info.id(), info.avatar());
            info.setAvatar(QImage());
        }
        d->users.append(info);
        d->map.insert(info.id(), &d->users.last());
    }
    endInsertRows();
}

void TUserModel::clear()
{
    B_D(TUserModel);
    d->lastUpdateDateTime = QDateTime().toUTC();
    if (d->users.isEmpty())
        return;
    d->map.clear();
    beginRemoveRows(QModelIndex(), 0, d->users.size() - 1);
    if (avatarStoredSeparately()) {
        foreach (const TUserInfo &info, d->users)
            removeAvatar(info.id());
    }
    d->users.clear();
    endRemoveRows();
}

int TUserModel::columnCount(const QModelIndex &) const
{
    return 14;
}

QVariant TUserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.column() > columnCount() - 1 || Qt::DisplayRole != role)
        return QVariant();
    TUserInfo info = userInfoAt(index.row());
    if (!info.isValid())
        return QVariant();
    switch (index.column()) {
    case 0:
        return info.id();
    case 1:
        return info.login();
    case 2:
        return info.email();
    case 3:
        return info.active();
    case 4:
        return info.accessLevel();
    case 5:
        return info.name();
    case 6:
        return info.patronymic();
    case 7:
        return info.surname();
    case 8:
        return info.availableServices();
    case 9:
        return info.groups();
    case 10:
        return info.availableGroups();
    case 11:
        if (avatarStoredSeparately())
            return loadAvatar(info.id());
        else
            return info.avatar();
    case 12:
        return info.registrationDateTime();
    case 13:
        return info.lastModificationDateTime();
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
        return tr("E-mail", "headerData");
    case 3:
        return tr("Active", "headerData");
    case 4:
        return tr("Access level", "headerData");
    case 5:
        return tr("Name", "headerData");
    case 6:
        return tr("Patronymic", "headerData");
    case 7:
        return tr("Surname", "headerData");
    case 8:
        return tr("Available services", "headerData");
    case 9:
        return tr("Groups", "headerData");
    case 10:
        return tr("Available groups", "headerData");
    case 11:
        return tr("Avatar", "headerData");
    case 12:
        return tr("Registration date", "headerData");
    case 13:
        return tr("Last modified", "headerData");
    default:
        return QVariant();
    }
}

QDateTime TUserModel::lastUpdateDateTime() const
{
    return d_func()->lastUpdateDateTime;
}

void TUserModel::removeUser(quint64 id)
{
    if (!id || !d_func()->map.contains(id))
        return;
    d_func()->map.remove(id);
    int ind = d_func()->indexOf(id);
    beginRemoveRows(QModelIndex(), ind, ind);
    d_func()->users.removeAt(ind);
    if (avatarStoredSeparately())
        removeAvatar(id);
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

void TUserModel::update(const TUserInfoList &newUsers, const TIdList &deletedUsers, const QDateTime &updateDateTime)
{
    removeUsers(deletedUsers);
    addUsers(newUsers);
    d_func()->lastUpdateDateTime = updateDateTime.toUTC();
}

void TUserModel::update(const TUserInfoList &newUsers, const QDateTime &updateDateTime)
{
    update(newUsers, TIdList(), updateDateTime);
}

void TUserModel::updateUser(quint64 userId, const TUserInfo &newInfo)
{
    TUserInfo *info = d_func()->map.value(userId);
    if (!info)
        return;
    int row = d_func()->indexOf(userId);
    *info = newInfo;
    if (avatarStoredSeparately()) {
        saveAvatar(userId, newInfo.avatar());
        info->setAvatar(QImage());
    }
    Q_EMIT dataChanged(index(row, 0), index(row, columnCount() - 1));
}

quint64 TUserModel::userIdAt(int index) const
{
    if (index < 0 || index >= d_func()->users.size())
        return 0;
    return d_func()->users.at(index).id();
}

TUserInfo TUserModel::userInfo(quint64 id) const
{
    const TUserInfo *info = id ? d_func()->map.value(id) : 0;
    if (!info)
        return TUserInfo();
    if (!avatarStoredSeparately())
        return *info;
    TUserInfo iinfo = *info;
    iinfo.setAvatar(loadAvatar(info->id()));
    return iinfo;
}

TUserInfo TUserModel::userInfoAt(int index) const
{
    if (index < 0 || index >= d_func()->users.size())
        return TUserInfo();
    TUserInfo info = d_func()->users.at(index);
    if (!avatarStoredSeparately())
        return info;
    TUserInfo iinfo = info;
    iinfo.setAvatar(loadAvatar(info.id()));
    return iinfo;
}

/*============================== Protected methods =========================*/

bool TUserModel::avatarStoredSeparately() const
{
    return false;
}

QImage TUserModel::loadAvatar(quint64) const
{
    return QImage();
}

void TUserModel::removeAvatar(quint64)
{
    //
}

void TUserModel::saveAvatar(quint64, const QImage &)
{
    //
}
