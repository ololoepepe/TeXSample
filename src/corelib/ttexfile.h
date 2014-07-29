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

#ifndef TTEXFILE_H
#define TTEXFILE_H

class TTexFilePrivate;

class QDataStream;
class QDebug;
class QStringList;
class QTextCodec;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TTexFile ====================================
============================================================================*/

class T_CORE_EXPORT TTexFile : BBase
{
    B_DECLARE_PRIVATE(TTexFile)
public:
    explicit TTexFile(const QString &fileName = QString(), QTextCodec *codec = 0, const QString &subpath = QString());
    TTexFile(const TTexFile &other);
    ~TTexFile();
public:
    void clear();
    QStringList externalFileNames(bool *ok = 0) const;
    QString fileName() const;
    bool isValid() const;
    bool load(const QString &fileName, QTextCodec *codec = 0, const QString &subpath = QString());
    bool prependExternalFileNames(const QString &subpath);
    QString relativeFileName() const;
    void removeRestrictedCommands();
    QStringList restrictedCommands() const;
    bool save(const QString &dir, QTextCodec *codec = 0) const;
    void setFileName(const QString &fileName);
    void setRelativeFileName(const QString &relativeFileName);
    void setSubpath(const QString &subpath);
    void setText(const QString &text);
    int size() const;
    QString subpath() const;
    QString text() const;
public:
    TTexFile &operator =(const TTexFile &other);
    bool operator ==(const TTexFile &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TTexFile &file);
    friend QDataStream &operator >>(QDataStream &stream, TTexFile &file);
    friend QDebug operator <<(QDebug dbg, const TTexFile &file);
};

Q_DECLARE_METATYPE(TTexFile)

#endif // TTEXFILE_H
