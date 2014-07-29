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

#include "ttexcompiler.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QList>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TTexCompilerPrivate =========================
============================================================================*/

class TTexCompilerPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TTexCompiler)
public:
    TTexCompiler::Compiler compiler;
public:
    explicit TTexCompilerPrivate(TTexCompiler *q);
    ~TTexCompilerPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TTexCompilerPrivate)
};


/*============================================================================
================================ TTexCompilerPrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TTexCompilerPrivate::TTexCompilerPrivate(TTexCompiler *q) :
    BBasePrivate(q)
{
    //
}

TTexCompilerPrivate::~TTexCompilerPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TTexCompilerPrivate::init()
{
    compiler = TTexCompiler::Unknown;
}

/*============================================================================
================================ TTexCompiler ================================
============================================================================*/

/*============================== Public constructors =======================*/

TTexCompiler::TTexCompiler(int compiler) :
    BBase(*new TTexCompilerPrivate(this))
{
    d_func()->init();
    *this = compiler;
}

TTexCompiler::TTexCompiler(const TTexCompiler &other) :
    BBase(*new TTexCompilerPrivate(this))
{
    d_func()->init();
    *this = other;
}

TTexCompiler::~TTexCompiler()
{
    //
}

/*============================== Static public methods =====================*/

QList<TTexCompiler> TTexCompiler::allCompilers(bool includeUnknown)
{
    QList<TTexCompiler> list = QList<TTexCompiler>() << Tex << Latex << Pdftex << Pdflatex;
    if (includeUnknown)
        list.prepend(Unknown);
    return list;
}

QString TTexCompiler::compilerToString(Compiler compiler)
{
    switch (compiler)
    {
    case Tex:
        return "TeX";
    case Latex:
        return "LaTeX";
    case Pdftex:
        return "PdfTeX";
    case Pdflatex:
        return "PdfLaTeX";
    case Unknown:
    default:
        return "";
    }
}

/*============================== Public methods ============================*/

bool TTexCompiler::isValid() const
{
    return Unknown != d_func()->compiler;
}

QString TTexCompiler::toString() const
{
    return compilerToString(d_func()->compiler);
}

/*============================== Public operators ==========================*/

TTexCompiler &TTexCompiler::operator =(const TTexCompiler &other)
{
    B_D(TTexCompiler);
    const TTexCompilerPrivate *dd = other.d_func();
    d->compiler = dd->compiler;
    return *this;
}

TTexCompiler &TTexCompiler::operator =(int compiler)
{
    d_func()->compiler = enum_cast<Compiler>(compiler, Unknown, Pdflatex);
    return *this;
}

bool TTexCompiler::operator ==(const TTexCompiler &other) const
{
    const B_D(TTexCompiler);
    const TTexCompilerPrivate *dd = other.d_func();
    return d->compiler == dd->compiler;
}

bool TTexCompiler::operator !=(const TTexCompiler &other) const
{
    return !(*this == other);
}

TTexCompiler::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TTexCompiler::operator int() const
{
    return d_func()->compiler;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TTexCompiler &data)
{
    const TTexCompilerPrivate *d = data.d_func();
    QVariantMap m;
    m.insert("compiler", int(d->compiler));
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TTexCompiler &data)
{
    TTexCompilerPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->compiler = enum_cast<TTexCompiler::Compiler>(m.value("compiler"), TTexCompiler::Unknown,
                                                    TTexCompiler::Pdflatex);
    return stream;
}

QDebug operator <<(QDebug dbg, const TTexCompiler &/*data*/)
{
    //const TTexCompilerPrivate *d = data.d_func();
    dbg.nospace() << "TTexCompiler(" << ")";
    return dbg.space();
}
