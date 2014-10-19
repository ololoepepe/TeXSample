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

#ifndef TEDITLABREQUESTDATA_H
#define TEDITLABREQUESTDATA_H

class TEditLabRequestDataPrivate;

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
================================ TEditLabRequestData =========================
============================================================================*/

class T_CORE_EXPORT TEditLabRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditLabRequestData)
public:
    explicit TEditLabRequestData();
    TEditLabRequestData(const TEditLabRequestData &other);
    ~TEditLabRequestData();
public:
    TAuthorInfoList authors() const;
    void clear();
    TLabDataList dataList() const;
    QStringList deletedExtraFiles() const;
    QString description() const;
    bool editData() const;
    TIdList groups() const;
    quint64 id() const;
    bool isValid() const;
    TBinaryFileList newExtraFiles() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setDataList(const TLabDataList &dataList);
    void setDeletedExtraFiles(const QStringList &extraFiles);
    void setDescritpion(const QString &description);
    void setEditData(bool edit);
    void setGroups(const TIdList &groups);
    void setId(quint64 id);
    void setNewExtraFiles(const TBinaryFileList &extraFiles);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TEditLabRequestData &operator =(const TEditLabRequestData &other);
    bool operator ==(const TEditLabRequestData &other) const;
    bool operator !=(const TEditLabRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TEditLabRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TEditLabRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TEditLabRequestData &data);
};

Q_DECLARE_METATYPE(TEditLabRequestData)

#endif // TEDITLABREQUESTDATA_H
