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

#ifndef TEDITSAMPLEADMINREQUESTDATA_H
#define TEDITSAMPLEADMINREQUESTDATA_H

class TEditSampleAdminRequestDataPrivate;

class TAuthorInfoList;
class TSampleType;
class TTexProject;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditSampleAdminRequestData =================
============================================================================*/

class T_CORE_EXPORT TEditSampleAdminRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditSampleAdminRequestData)
public:
    explicit TEditSampleAdminRequestData();
    TEditSampleAdminRequestData(const TEditSampleAdminRequestData &other);
    ~TEditSampleAdminRequestData();
public:
    QString adminRemark() const;
    TAuthorInfoList authors() const;
    void clear();
    QString description() const;
    bool editProject() const;
    quint64 id() const;
    bool isValid() const;
    TTexProject project() const;
    quint8 rating() const;
    void setAdminRemark(const QString &remark);
    void setAuthors(const TAuthorInfoList &authors);
    void setDescritpion(const QString &description);
    void setEditProject(bool edit);
    void setId(quint64 id);
    void setProject(const TTexProject &project);
    void setRating(quint8 rating);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    void setType(const TSampleType &type);
    QStringList tags() const;
    QString title() const;
    TSampleType type() const;
public:
    TEditSampleAdminRequestData &operator =(const TEditSampleAdminRequestData &other);
    bool operator ==(const TEditSampleAdminRequestData &other) const;
    bool operator !=(const TEditSampleAdminRequestData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TEditSampleAdminRequestData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TEditSampleAdminRequestData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TEditSampleAdminRequestData &data);
};

Q_DECLARE_METATYPE(TEditSampleAdminRequestData)

#endif // TEDITSAMPLEADMINREQUESTDATA_H
