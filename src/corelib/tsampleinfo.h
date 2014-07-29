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

#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H

class TSampleInfoPrivate;

class TAuthorInfoList;
class TFileInfo;
class TFileInfoList;
class TSampleType;

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
================================ TSampleInfo =================================
============================================================================*/

class T_CORE_EXPORT TSampleInfo : public BBase
{
    B_DECLARE_PRIVATE(TSampleInfo)
public:
    explicit TSampleInfo();
    TSampleInfo(const TSampleInfo &other);
    ~TSampleInfo();
protected:
    explicit TSampleInfo(TSampleInfoPrivate &d);
public:
    QString adminRemark() const;
    TAuthorInfoList authors() const;
    void clear();
    QDateTime creationDateTime() const;
    QString description() const;
    TFileInfoList extraPreviewFiles() const;
    TFileInfoList extraSourceFiles() const;
    quint64 id() const;
    bool isValid() const;
    QDateTime lastModificationDateTime() const;
    TFileInfo mainPreviewFile() const;
    TFileInfo mainSourceFile() const;
    int previewSize() const;
    quint8 rating() const;
    quint64 senderId() const;
    QString senderLogin() const;
    void setAdminRemark(const QString &remark);
    void setAuthors(const TAuthorInfoList &authors);
    void setCreationDateTime(const QDateTime &dt);
    void setDescription(const QString &description);
    void setExtraPreviewFiles(const TFileInfoList &files);
    void setExtraSourceFiles(const TFileInfoList &files);
    void setId(quint64 id);
    void setLastModificationDateTime(const QDateTime &dt);
    void setMainPreviewFile(const TFileInfo &file);
    void setMainSourceFile(const TFileInfo &file);
    void setRating(quint8 r);
    void setSenderId(quint64 id);
    void setSenderLogin(const QString &login);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    void setType(const TSampleType &type);
    int sourceSize() const;
    QStringList tags() const;
    QString title() const;
    TSampleType type() const;
public:
    TSampleInfo &operator =(const TSampleInfo &other);
    bool operator ==(const TSampleInfo &other) const;
    bool operator !=(const TSampleInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TSampleInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TSampleInfo &info);
    friend QDebug operator <<(QDebug dbg, const TSampleInfo &info);
};

Q_DECLARE_METATYPE(TSampleInfo)

#endif // TSAMPLEINFO_H
