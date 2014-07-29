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

#ifndef TGETSAMPLEPREVIEWREPLYDATA_H
#define TGETSAMPLEPREVIEWREPLYDATA_H

class TGetSamplePreviewReplyDataPrivate;

class TBinaryFile;
class TBinaryFileList;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSamplePreviewReplyData ==================
============================================================================*/

class T_CORE_EXPORT TGetSamplePreviewReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetSamplePreviewReplyData)
public:
    explicit TGetSamplePreviewReplyData();
    TGetSamplePreviewReplyData(const TGetSamplePreviewReplyData &other);
    ~TGetSamplePreviewReplyData();
public:
    TBinaryFileList &extraFiles();
    const TBinaryFileList &extraFiles() const;
    TBinaryFile &mainFile();
    const TBinaryFile &mainFile() const;
    void setExtraFiles(const TBinaryFileList &extraFiles);
    void setMainFile(const TBinaryFile &file);
public:
    TGetSamplePreviewReplyData &operator =(const TGetSamplePreviewReplyData &other);
    bool operator ==(const TGetSamplePreviewReplyData &other) const;
    bool operator !=(const TGetSamplePreviewReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSamplePreviewReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSamplePreviewReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSamplePreviewReplyData &data);
};

Q_DECLARE_METATYPE(TGetSamplePreviewReplyData)

#endif // TGETSAMPLEPREVIEWREPLYDATA_H
