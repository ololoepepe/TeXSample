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

#ifndef TREPLY_H
#define TREPLY_H

class TReplyPrivate;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TReply ======================================
============================================================================*/

class T_CORE_EXPORT TReply : public BBase
{
    B_DECLARE_PRIVATE(TReply)
public:
    explicit TReply();
    explicit TReply(const QString &message);
    TReply(const TReply &other);
    ~TReply();
public:
    bool cacheUpToDate() const;
    void clear();
    QVariant data() const;
    bool isValid() const;
    QString message() const;
    QDateTime requestDateTime() const;
    void setCacheUpToDate(bool upToDate);
    void setData(const QVariant &data);
    void setMessage(const QString &message);
    void setRequestDateTime(const QDateTime &dt);
    void setSuccess(bool success);
    bool success() const;
public:
    TReply &operator =(const TReply &other);
    bool operator ==(const TReply &other) const;
    bool operator !=(const TReply &other) const;
    operator QVariant() const;
    operator bool() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TReply &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TReply &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TReply &data);
};

Q_DECLARE_METATYPE(TReply)

#endif // TREPLY_H
