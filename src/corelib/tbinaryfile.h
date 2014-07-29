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

#ifndef TBINARYFILE_H
#define TBINARYFILE_H

class TBinaryFilePrivate;

class QByteArray;
class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TBinaryFile =================================
============================================================================*/

class T_CORE_EXPORT TBinaryFile : BBase
{
    B_DECLARE_PRIVATE(TBinaryFile)
public:
    explicit TBinaryFile(const QString &fileaName = QString(), const QString &subpath = QString());
    TBinaryFile(const TBinaryFile &other);
    ~TBinaryFile();
public:
    void clear();
    QByteArray data() const;
    QString description() const;
    QString fileName() const;
    bool isValid() const;
    bool load(const QString &fileName, const QString &subpath = QString());
    bool mayBeExecutable() const;
    QString relativeFileName() const;
    bool save(const QString &dir) const;
    void setData(const QByteArray &data);
    void setDescription(const QString &description);
    void setFileName(const QString &fileName);
    void setRelativeFileName(const QString &relativeFileName);
    void setSubpath(const QString &subpath);
    int size() const;
    QString subpath() const;
public:
    TBinaryFile &operator =(const TBinaryFile &other);
    bool operator ==(const TBinaryFile &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TBinaryFile &file);
    friend QDataStream &operator >>(QDataStream &stream, TBinaryFile &file);
    friend QDebug operator <<(QDebug dbg, const TBinaryFile &file);
};

Q_DECLARE_METATYPE(TBinaryFile)

#endif // TBINARYFILE_H
