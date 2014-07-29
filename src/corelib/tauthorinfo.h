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

#ifndef TAUTHORINFO_H
#define TAUTHORINFO_H

class TAuthorInfoPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAuthorInfo =================================
============================================================================*/

class T_CORE_EXPORT TAuthorInfo : public BBase
{
    B_DECLARE_PRIVATE(TAuthorInfo)
public:
    explicit TAuthorInfo();
    TAuthorInfo(const TAuthorInfo &other);
    ~TAuthorInfo();
public:
    void clear();
    bool isValid() const;
    QString name() const;
    QString organization() const;
    QString patronymic() const;
    QString post() const;
    QString role() const;
    void setName(const QString &name);
    void setOrganization(const QString &organization);
    void setPatronymic(const QString &patronymic);
    void setPost(const QString &post);
    void setRole(const QString &role);
    void setSurname(const QString &surname);
    QString surname() const;
public:
    TAuthorInfo &operator =(const TAuthorInfo &other);
    bool operator ==(const TAuthorInfo &other) const;
    bool operator !=(const TAuthorInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAuthorInfo &data);
    friend QDataStream &operator >>(QDataStream &stream, TAuthorInfo &data);
    friend QDebug operator <<(QDebug dbg, const TAuthorInfo &data);
};

Q_DECLARE_METATYPE(TAuthorInfo)

#endif // TAUTHORINFO_H
