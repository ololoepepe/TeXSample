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

#ifndef TINVITEMODEL_H
#define TINVITEMODEL_H

class TInviteModelPrivate;

class TIdList;
class TInviteInfo;
class TInviteInfoList;

class QObject;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QAbstractTableModel>
#include <QDateTime>
#include <QModelIndex>

/*============================================================================
================================ TInviteModel ================================
============================================================================*/

class T_CORE_EXPORT TInviteModel : public QAbstractTableModel, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TInviteModel)
public:
    explicit TInviteModel(QObject *parent = 0);
    ~TInviteModel();
public:
    void addInvite(const TInviteInfo &invite);
    void addInvites(const TInviteInfoList &inviteList);
    void clear();
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    TInviteInfo inviteInfo(quint64 id) const;
    TInviteInfo inviteInfoAt(int index) const;
    QDateTime lastUpdateDateTime() const;
    void removeInvite(quint64 id);
    void removeInvites(const TIdList &idList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    void update(const TInviteInfoList &newInvites, const TIdList &deletedInvites,
                const QDateTime &updateDateTime = QDateTime());
    void update(const TInviteInfoList &newInvites, const QDateTime &updateDateTime = QDateTime());
private:
    Q_DISABLE_COPY(TInviteModel)
};

#endif // TINVITEMODEL_H

