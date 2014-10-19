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

#ifndef TSUBSCRIBEREQUESTDATA_H
#define TSUBSCRIBEREQUESTDATA_H

class TSubscribeRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TSubscribeRequestData =======================
============================================================================*/

class T_CORE_EXPORT TSubscribeRequestData : public BBase
{
    B_DECLARE_PRIVATE(TSubscribeRequestData)
public:
    explicit TSubscribeRequestData();
    TSubscribeRequestData(const TSubscribeRequestData &other);
    ~TSubscribeRequestData();
public:
    void clear();
    bool isValid() const;
    void setSubscribedToLog(bool subscribed);
    bool subscribedToLog() const;
public:
    TSubscribeRequestData &operator =(const TSubscribeRequestData &other);
    bool operator ==(const TSubscribeRequestData &other) const;
    bool operator !=(const TSubscribeRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TSubscribeRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TSubscribeRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TSubscribeRequestData &data);
};

Q_DECLARE_METATYPE(TSubscribeRequestData)

#endif // TSUBSCRIBEREQUESTDATA_H
