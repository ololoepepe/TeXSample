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

#ifndef TUSERMODEL_H
#define TUSERMODEL_H

class TUserModelPrivate;

class TIdList;
class TUserInfo;
class TUserInfoList;

class QImage;
class QObject;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QAbstractTableModel>
#include <QModelIndex>

/*============================================================================
================================ TUserModel ==================================
============================================================================*/

class T_CORE_EXPORT TUserModel : public QAbstractTableModel, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TUserModel)
public:
    explicit TUserModel(QObject *parent = 0);
    ~TUserModel();
public:
    void addUser(const TUserInfo &user);
    void addUsers(const TUserInfoList &userList);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    const TUserInfo* userInfo(quint64 id) const;
    const TUserInfo* userInfoAt(int index) const;
    void removeUser(quint64 id);
    void removeUsers(const TIdList &idList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    void updateUser(quint64 userId, const TUserInfo &newInfo);
    void updateUserAvatar(quint64 userId, const QImage &avatar);
private:
    Q_DISABLE_COPY(TUserModel)
};

#endif // TUSERMODEL_H

