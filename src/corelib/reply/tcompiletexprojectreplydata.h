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

#ifndef TCOMPILETEXPROJECTREPLYDATA_H
#define TCOMPILETEXPROJECTREPLYDATA_H

class TCompileTexProjectReplyDataPrivate;

class TBinaryFileList;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TCompileTexProjectReplyData =================
============================================================================*/

class T_CORE_EXPORT TCompileTexProjectReplyData : public BBase
{
    B_DECLARE_PRIVATE(TCompileTexProjectReplyData)
public:
    explicit TCompileTexProjectReplyData();
    TCompileTexProjectReplyData(const TCompileTexProjectReplyData &other);
    ~TCompileTexProjectReplyData();
public:
    int dvipsExitCode() const;
    QString dvipsOutput() const;
    int exitCode() const;
    const TBinaryFileList &files() const;
    int makeindexExitCode() const;
    QString makeindexOutput() const;
    QString output() const;
    void setDvipsExitCode(int code);
    void setDvipsOutput(const QString &output);
    void setExitCode(int code);
    void setFiles(const TBinaryFileList &files);
    void setMakeindexExitCode(int code);
    void setMakeindexOutput(const QString &output);
    void setOutput(const QString &output);
public:
    TCompileTexProjectReplyData &operator =(const TCompileTexProjectReplyData &other);
    bool operator ==(const TCompileTexProjectReplyData &other) const;
    bool operator !=(const TCompileTexProjectReplyData &other) const;
    operator QVariant() const;
public:
    T_CORE_EXPORT friend QDataStream &operator <<(QDataStream &stream, const TCompileTexProjectReplyData &data);
    T_CORE_EXPORT friend QDataStream &operator >>(QDataStream &stream, TCompileTexProjectReplyData &data);
    T_CORE_EXPORT friend QDebug operator <<(QDebug dbg, const TCompileTexProjectReplyData &data);
};

Q_DECLARE_METATYPE(TCompileTexProjectReplyData)

#endif // TCOMPILETEXPROJECTREPLYDATA_H
