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

#ifndef TCONFIRMEMAILCHANGEREPLYDATA_H
#define TCONFIRMEMAILCHANGEREPLYDATA_H

class TConfirmEmailChangeReplyDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TConfirmEmailChangeReplyData ================
============================================================================*/

class T_CORE_EXPORT TConfirmEmailChangeReplyData : public BBase
{
    B_DECLARE_PRIVATE(TConfirmEmailChangeReplyData)
public:
    explicit TConfirmEmailChangeReplyData();
    TConfirmEmailChangeReplyData(const TConfirmEmailChangeReplyData &other);
    ~TConfirmEmailChangeReplyData();
public:
    void setSuccess(bool success);
    bool success() const;
public:
    TConfirmEmailChangeReplyData &operator =(const TConfirmEmailChangeReplyData &other);
    bool operator ==(const TConfirmEmailChangeReplyData &other) const;
    bool operator !=(const TConfirmEmailChangeReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TConfirmEmailChangeReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TConfirmEmailChangeReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TConfirmEmailChangeReplyData &data);
};

Q_DECLARE_METATYPE(TConfirmEmailChangeReplyData)

#endif // TCONFIRMEMAILCHANGEREPLYDATA_H
