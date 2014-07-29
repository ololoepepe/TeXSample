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

#ifndef TFILEINFO_H
#define TFILEINFO_H

class TFileInfoPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TFileInfo ===================================
============================================================================*/

class T_CORE_EXPORT TFileInfo : public BBase
{
    B_DECLARE_PRIVATE(TFileInfo)
public:
    explicit TFileInfo();
    TFileInfo(const TFileInfo &other);
    ~TFileInfo();
public:
    void clear();
    QString description() const;
    QString fileName() const;
    int fileSize() const;
    bool isValid() const;
    void setDescription(const QString &description);
    void setFileName(const QString &fileName);
    void setFileSize(int size);
public:
    TFileInfo &operator =(const TFileInfo &other);
    bool operator ==(const TFileInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TFileInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TFileInfo &info);
    friend QDebug operator <<(QDebug dbg, const TFileInfo &info);
};

Q_DECLARE_METATYPE(TFileInfo)

#endif // TFILEINFO_H
