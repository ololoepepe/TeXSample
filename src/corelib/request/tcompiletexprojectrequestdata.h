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

#ifndef TCOMPILETEXPROJECTREQUESTDATA_H
#define TCOMPILETEXPROJECTREQUESTDATA_H

class TCompileTexProjectRequestDataPrivate;

class TTexCompiler;
class TTexProject;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QTextCodec;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCompileTexProjectRequestData ===============
============================================================================*/

class T_CORE_EXPORT TCompileTexProjectRequestData : public BBase
{
    B_DECLARE_PRIVATE(TCompileTexProjectRequestData)
public:
    explicit TCompileTexProjectRequestData();
    TCompileTexProjectRequestData(const TCompileTexProjectRequestData &other);
    ~TCompileTexProjectRequestData();
public:
    void clear();
    QTextCodec *codec() const;
    QStringList commands() const;
    TTexCompiler compiler() const;
    bool dvipsEnabled() const;
    bool isValid() const;
    bool makeindexEnabled() const;
    QStringList options() const;
    TTexProject project() const;
    void setCodec(QTextCodec *codec);
    void setCommands(const QStringList &commands);
    void setCompiler(const TTexCompiler &compiler);
    void setDvipsEnabled(bool enabled);
    void setMakeindexEnabled(bool enabled);
    void setOptions(const QStringList &options);
    void setProject(const TTexProject &project);
public:
    TCompileTexProjectRequestData &operator =(const TCompileTexProjectRequestData &other);
    bool operator ==(const TCompileTexProjectRequestData &other) const;
    bool operator !=(const TCompileTexProjectRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCompileTexProjectRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TCompileTexProjectRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TCompileTexProjectRequestData &data);
};

Q_DECLARE_METATYPE(TCompileTexProjectRequestData)

#endif // TCOMPILETEXPROJECTREQUESTDATA_H
