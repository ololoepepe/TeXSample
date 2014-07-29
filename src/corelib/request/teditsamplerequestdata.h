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

#ifndef TEDITSAMPLEREQUESTDATA_H
#define TEDITSAMPLEREQUESTDATA_H

class TEditSampleRequestDataPrivate;

class TAuthorInfoList;
class TIdList;
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
================================ TEditSampleRequestData ======================
============================================================================*/

class T_CORE_EXPORT TEditSampleRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditSampleRequestData)
public:
    explicit TEditSampleRequestData();
    TEditSampleRequestData(const TEditSampleRequestData &other);
    ~TEditSampleRequestData();
public:
    TAuthorInfoList authors() const;
    void clear();
    QString description() const;
    bool editProject() const;
    TIdList groups() const;
    bool isValid() const;
    TTexProject project() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setDescritpion(const QString &description);
    void setEditProject(bool edit);
    void setGroups(const TIdList &groups);
    void setProject(const TTexProject &project);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TEditSampleRequestData &operator =(const TEditSampleRequestData &other);
    bool operator ==(const TEditSampleRequestData &other) const;
    bool operator !=(const TEditSampleRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSampleRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSampleRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSampleRequestData &data);
};

Q_DECLARE_METATYPE(TEditSampleRequestData)

#endif // TEDITSAMPLEREQUESTDATA_H
