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

#ifndef TSETSERVERSTATEREQUESTDATA_H
#define TSETSERVERSTATEREQUESTDATA_H

class TSetServerStateRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TSetServerStateRequestData ==================
============================================================================*/

class T_CORE_EXPORT TSetServerStateRequestData : public BBase
{
    B_DECLARE_PRIVATE(TSetServerStateRequestData)
public:
    explicit TSetServerStateRequestData();
    TSetServerStateRequestData(const TSetServerStateRequestData &other);
    ~TSetServerStateRequestData();
public:
    QString address() const;
    void clear();
    bool listening();
    bool isValid();
    void setAddress(const QString &address);
    void setListening(bool listening);
public:
    TSetServerStateRequestData &operator =(const TSetServerStateRequestData &other);
    bool operator ==(const TSetServerStateRequestData &other) const;
    bool operator !=(const TSetServerStateRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TSetServerStateRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TSetServerStateRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TSetServerStateRequestData &data);
};

Q_DECLARE_METATYPE(TSetServerStateRequestData)

#endif // TSETSERVERSTATEREQUESTDATA_H
