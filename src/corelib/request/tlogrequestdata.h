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

#ifndef TLOGREQUESTDATA_H
#define TLOGREQUESTDATA_H

class TLogRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BLogger>

#include <QMetaType>

/*============================================================================
================================ TLogRequestData =============================
============================================================================*/

class T_CORE_EXPORT TLogRequestData : public BBase
{
    B_DECLARE_PRIVATE(TLogRequestData)
public:
    explicit TLogRequestData();
    TLogRequestData(const TLogRequestData &other);
    ~TLogRequestData();
public:
    void clear();
    bool isValid() const;
    BLogger::Level level() const;
    void setLevel(BLogger::Level level);
    void setText(const QString &text);
    QString text() const;
public:
    TLogRequestData &operator =(const TLogRequestData &other);
    bool operator ==(const TLogRequestData &other) const;
    bool operator !=(const TLogRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TLogRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TLogRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TLogRequestData &data);
};

Q_DECLARE_METATYPE(TLogRequestData)

#endif // TLOGREQUESTDATA_H
