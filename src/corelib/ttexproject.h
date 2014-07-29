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

#ifndef TTEXPROJECT_H
#define TTEXPROJECT_H

class TTexProjectPrivate;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QTextCodec;
class QVariant;

#include "tbinaryfile.h"
#include "ttexfile.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TTexProject =================================
============================================================================*/

class T_CORE_EXPORT TTexProject : BBase
{
    B_DECLARE_PRIVATE(TTexProject)
public:
    explicit TTexProject();
    TTexProject(const TTexProject &other);
    ~TTexProject();
public:
    QList<TBinaryFile> &binaryFiles();
    const QList<TBinaryFile> &binaryFiles() const;
    void clear();
    bool isValid() const;
    bool load(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec = 0);
    bool load(const QString &rootFileName, QTextCodec *codec = 0);
    bool prependExternalFileNames(const QString &subpath);
    void removeRestrictedCommands();
    QStringList restrictedCommands() const;
    TTexFile &rootFile();
    const TTexFile &rootFile() const;
    bool save(const QString &dir, QTextCodec *codec = 0) const;
    int size() const;
    QList<TTexFile> &texFiles();
    const QList<TTexFile> &texFiles() const;
public:
    TTexProject &operator =(const TTexProject &other);
    bool operator ==(const TTexProject &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TTexProject &project);
    friend QDataStream &operator >>(QDataStream &stream, TTexProject &project);
    friend QDebug operator <<(QDebug dbg, const TTexProject &project);
};

Q_DECLARE_METATYPE(TTexProject)

#endif // TTEXPROJECT_H
