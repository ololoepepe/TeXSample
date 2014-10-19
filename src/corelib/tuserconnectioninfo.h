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

#ifndef TUSERCONNECTIONINFO_H
#define TUSERCONNECTIONINFO_H

class TUserConnectionInfoPrivate;

class TClientInfo;
class TUserInfo;

class BUuid;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TUserConnectionInfo =========================
============================================================================*/

class T_CORE_EXPORT TUserConnectionInfo : public BBase
{
    B_DECLARE_PRIVATE(TUserConnectionInfo)
public:
    explicit TUserConnectionInfo();
    TUserConnectionInfo(const TUserConnectionInfo &other);
    ~TUserConnectionInfo();
public:
    void clear();
    TClientInfo clientInfo() const;
    QDateTime connectionDateTime() const;
    bool isValid() const;
    QString peerAddress() const;
    void setClientInfo(const TClientInfo &info);
    void setConnectionDateTime(const QDateTime &dt);
    void setPeerAddress(const QString &address);
    void setUniqueId(const BUuid &id);
    void setUptime(qint64 msecs);
    void setUserInfo(const TUserInfo &info);
    BUuid uniqueId() const;
    qint64 uptime() const;
    TUserInfo userInfo() const;
public:
    TUserConnectionInfo &operator =(const TUserConnectionInfo &other);
    bool operator ==(const TUserConnectionInfo &other) const;
    bool operator !=(const TUserConnectionInfo &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TUserConnectionInfo &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TUserConnectionInfo &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TUserConnectionInfo &data);
};

Q_DECLARE_METATYPE(TUserConnectionInfo)

#endif // TUSERCONNECTIONINFO_H
