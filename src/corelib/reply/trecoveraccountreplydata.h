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

#ifndef TRECOVERACCOUNTREPLYDATA_H
#define TRECOVERACCOUNTREPLYDATA_H

class TRecoverAccountReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRecoverAccountReplyData ====================
============================================================================*/

class T_CORE_EXPORT TRecoverAccountReplyData : public BBase
{
    B_DECLARE_PRIVATE(TRecoverAccountReplyData)
public:
    explicit TRecoverAccountReplyData();
    TRecoverAccountReplyData(const TRecoverAccountReplyData &other);
    ~TRecoverAccountReplyData();
public:
    void setSuccess(bool success);
    bool success() const;
public:
    TRecoverAccountReplyData &operator =(const TRecoverAccountReplyData &other);
    bool operator ==(const TRecoverAccountReplyData &other) const;
    bool operator !=(const TRecoverAccountReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TRecoverAccountReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TRecoverAccountReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TRecoverAccountReplyData &data);
};

Q_DECLARE_METATYPE(TRecoverAccountReplyData)

#endif // TRECOVERACCOUNTREPLYDATA_H
