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

#ifndef TREQUESTRECOVERYCODEREPLYDATA_H
#define TREQUESTRECOVERYCODEREPLYDATA_H

class TRequestRecoveryCodeReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRequestRecoveryCodeReplyData ===============
============================================================================*/

class T_CORE_EXPORT TRequestRecoveryCodeReplyData : public BBase
{
    B_DECLARE_PRIVATE(TRequestRecoveryCodeReplyData)
public:
    explicit TRequestRecoveryCodeReplyData();
    TRequestRecoveryCodeReplyData(const TRequestRecoveryCodeReplyData &other);
    ~TRequestRecoveryCodeReplyData();
public:
    TRequestRecoveryCodeReplyData &operator =(const TRequestRecoveryCodeReplyData &other);
    bool operator ==(const TRequestRecoveryCodeReplyData &other) const;
    bool operator !=(const TRequestRecoveryCodeReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRequestRecoveryCodeReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TRequestRecoveryCodeReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TRequestRecoveryCodeReplyData &data);
};

Q_DECLARE_METATYPE(TRequestRecoveryCodeReplyData)

#endif // TREQUESTRECOVERYCODEREPLYDATA_H
