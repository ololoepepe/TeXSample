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

#ifndef TLABINFO_H
#define TLABINFO_H

class TLabInfoPrivate;

class TAuthorInfoList;
class TFileInfoList;
class TIdList;
class TLabDataInfoList;

class QDataStream;
class QDateTime;
class QDebug;
class QString;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TLabInfo ====================================
============================================================================*/

class T_CORE_EXPORT TLabInfo : public BBase
{
    B_DECLARE_PRIVATE(TLabInfo)
public:
    explicit TLabInfo();
    TLabInfo(const TLabInfo &other);
    ~TLabInfo();
protected:
    explicit TLabInfo(TLabInfoPrivate &d);
public:
    TAuthorInfoList authors() const;
    void clear();
    QDateTime creationDateTime() const;
    TLabDataInfoList dataInfos() const;
    QString description() const;
    TFileInfoList extraFiles() const;
    TIdList groups() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    quint64 senderId() const;
    QString senderLogin() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setCreationDateTime(const QDateTime &dt);
    void setDataInfos(const TLabDataInfoList &dataInfos);
    void setDescription(const QString &description);
    void setExtraFiles(const TFileInfoList &extraFiles);
    void setGroups(const TIdList &groups);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setSenderId(quint64 id);
    void setSenderLogin(const QString &login);
    void setTags(const QStringList &list);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TLabInfo &operator =(const TLabInfo &other);
    bool operator ==(const TLabInfo &other) const;
    bool operator !=(const TLabInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TLabInfo &info);
    friend QDebug operator <<(QDebug dbg, const TLabInfo &info);
};

Q_DECLARE_METATYPE(TLabInfo)

#endif // TLABINFO_H
