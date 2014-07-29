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

#ifndef TEDITSAMPLEADMINREPLYDATA_H
#define TEDITSAMPLEADMINREPLYDATA_H

class TEditSampleAdminReplyDataPrivate;

class TSampleInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditSampleAdminReplyData ===================
============================================================================*/

class T_CORE_EXPORT TEditSampleAdminReplyData : public BBase
{
    B_DECLARE_PRIVATE(TEditSampleAdminReplyData)
public:
    explicit TEditSampleAdminReplyData();
    TEditSampleAdminReplyData(const TEditSampleAdminReplyData &other);
    ~TEditSampleAdminReplyData();
public:
    TSampleInfo sampleInfo() const;
    void setSampleInfo(const TSampleInfo &info);
public:
    TEditSampleAdminReplyData &operator =(const TEditSampleAdminReplyData &other);
    bool operator ==(const TEditSampleAdminReplyData &other) const;
    bool operator !=(const TEditSampleAdminReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSampleAdminReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSampleAdminReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSampleAdminReplyData &data);
};

Q_DECLARE_METATYPE(TEditSampleAdminReplyData)

#endif // TEDITSAMPLEADMINREPLYDATA_H
