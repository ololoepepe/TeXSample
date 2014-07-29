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

#ifndef TADDSAMPLEREQUESTDATA_H
#define TADDSAMPLEREQUESTDATA_H

class TAddSampleRequestDataPrivate;

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
================================ TAddSampleRequestData =======================
============================================================================*/

class T_CORE_EXPORT TAddSampleRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAddSampleRequestData)
public:
    explicit TAddSampleRequestData();
    TAddSampleRequestData(const TAddSampleRequestData &other);
    ~TAddSampleRequestData();
public:
    TAuthorInfoList authors() const;
    void clear();
    QString description() const;
    TIdList groups() const;
    bool isValid() const;
    TTexProject project() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setDescritpion(const QString &description);
    void setGroups(const TIdList &groups);
    void setProject(const TTexProject &project);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TAddSampleRequestData &operator =(const TAddSampleRequestData &other);
    bool operator ==(const TAddSampleRequestData &other) const;
    bool operator !=(const TAddSampleRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddSampleRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddSampleRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAddSampleRequestData &data);
};

Q_DECLARE_METATYPE(TAddSampleRequestData)

#endif // TADDSAMPLEREQUESTDATA_H
