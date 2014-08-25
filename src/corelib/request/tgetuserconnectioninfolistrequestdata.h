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

#ifndef TGETUSERCONNECTIONINFOLISTREQUESTDATA_H
#define TGETUSERCONNECTIONINFOLISTREQUESTDATA_H

class TGetUserConnectionInfoListRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetUserConnectionInfoListRequestData =======
============================================================================*/

class T_CORE_EXPORT TGetUserConnectionInfoListRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetUserConnectionInfoListRequestData)
public:
    enum MatchType
    {
        MatchLogin = 0x01,
        MatchUniqueId = 0x02,
        MatchLoginAndUniqueId = MatchLogin | MatchUniqueId
    };
public:
    explicit TGetUserConnectionInfoListRequestData();
    TGetUserConnectionInfoListRequestData(const TGetUserConnectionInfoListRequestData &other);
    ~TGetUserConnectionInfoListRequestData();
public:
    void clear();
    bool isValid() const;
    QString matchPattern() const;
    MatchType matchType() const;
    void setMatchPattern(const QString &pattern);
    void setMatchType(MatchType type);
public:
    TGetUserConnectionInfoListRequestData &operator =(const TGetUserConnectionInfoListRequestData &other);
    bool operator ==(const TGetUserConnectionInfoListRequestData &other) const;
    bool operator !=(const TGetUserConnectionInfoListRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetUserConnectionInfoListRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetUserConnectionInfoListRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetUserConnectionInfoListRequestData &data);
};

Q_DECLARE_METATYPE(TGetUserConnectionInfoListRequestData)

#endif // TGETUSERCONNECTIONINFOLISTREQUESTDATA_H
