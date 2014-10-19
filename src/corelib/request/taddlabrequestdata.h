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

#ifndef TADDLABREQUESTDATA_H
#define TADDLABREQUESTDATA_H

class TAddLabRequestDataPrivate;

class TAuthorInfoList;
class TBinaryFileList;
class TIdList;
class TLabDataList;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddLabRequestData ==========================
============================================================================*/

class T_CORE_EXPORT TAddLabRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAddLabRequestData)
public:
    explicit TAddLabRequestData();
    TAddLabRequestData(const TAddLabRequestData &other);
    ~TAddLabRequestData();
public:
    TAuthorInfoList authors() const;
    void clear();
    TLabDataList dataList() const;
    QString description() const;
    TBinaryFileList extraFiles() const;
    TIdList groups() const;
    bool isValid() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setDataList(const TLabDataList &dataList);
    void setDescritpion(const QString &description);
    void setExtraFiles(const TBinaryFileList &extraFiles);
    void setGroups(const TIdList &groups);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TAddLabRequestData &operator =(const TAddLabRequestData &other);
    bool operator ==(const TAddLabRequestData &other) const;
    bool operator !=(const TAddLabRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TAddLabRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TAddLabRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TAddLabRequestData &data);
};

Q_DECLARE_METATYPE(TAddLabRequestData)

#endif // TADDLABREQUESTDATA_H
