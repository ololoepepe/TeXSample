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

#ifndef TTEXCOMPILER_H
#define TTEXCOMPILER_H

class TTexCompilerPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QList>
#include <QMetaType>

/*============================================================================
================================ TTexCompiler ================================
============================================================================*/

class T_CORE_EXPORT TTexCompiler : public BBase
{
    B_DECLARE_PRIVATE(TTexCompiler)
    Q_DECLARE_TR_FUNCTIONS(TTexCompiler)
public:
    enum Compiler
    {
        Unknown = 0,
        Tex,
        Latex,
        Pdftex,
        Pdflatex
    };
public:
    TTexCompiler(int compiler = Unknown);
    TTexCompiler(const TTexCompiler &other);
    ~TTexCompiler();
public:
    static QList<TTexCompiler> allCompilers(bool includeUnknown = false);
    static QString compilerToString(Compiler compiler);
public:
    bool isValid() const;
    QString toString() const;
public:
    TTexCompiler &operator =(const TTexCompiler &other);
    TTexCompiler &operator =(int compiler);
    bool operator ==(const TTexCompiler &other) const;
    bool operator !=(const TTexCompiler &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TTexCompiler &data);
    friend QDataStream &operator >>(QDataStream &stream, TTexCompiler &data);
    friend QDebug operator <<(QDebug dbg, const TTexCompiler &data);
};

Q_DECLARE_METATYPE(TTexCompiler)

#endif // TTEXCOMPILER_H
