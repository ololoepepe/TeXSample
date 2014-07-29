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

#include "tcompiletexprojectrequestdata.h"

#include "ttexcompiler.h"
#include "ttexproject.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TCompileTexProjectRequestDataPrivate ========
============================================================================*/

class TCompileTexProjectRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCompileTexProjectRequestData)
public:
    QTextCodec *codec;
    QStringList commands;
    TTexCompiler compiler;
    bool dvipsEnabled;
    bool makeindexEnabled;
    QStringList options;
    TTexProject project;
public:
    explicit TCompileTexProjectRequestDataPrivate(TCompileTexProjectRequestData *q);
    ~TCompileTexProjectRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TCompileTexProjectRequestDataPrivate)
};

/*============================================================================
================================ TCompileTexProjectRequestDataPrivate ========
============================================================================*/

/*============================== Public constructors =======================*/

TCompileTexProjectRequestDataPrivate::TCompileTexProjectRequestDataPrivate(TCompileTexProjectRequestData *q) :
    BBasePrivate(q)
{
    //
}

TCompileTexProjectRequestDataPrivate::~TCompileTexProjectRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCompileTexProjectRequestDataPrivate::init()
{
    codec = 0;
    dvipsEnabled = false;
    makeindexEnabled = false;
}

/*============================================================================
================================ TCompileTexProjectRequestData ===============
============================================================================*/

/*============================== Public constructors =======================*/

TCompileTexProjectRequestData::TCompileTexProjectRequestData() :
    BBase(*new TCompileTexProjectRequestDataPrivate(this))
{
    d_func()->init();
}

TCompileTexProjectRequestData::TCompileTexProjectRequestData(const TCompileTexProjectRequestData &other) :
    BBase(*new TCompileTexProjectRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCompileTexProjectRequestData::~TCompileTexProjectRequestData()
{
    //
}

/*============================== Public methods ============================*/

void TCompileTexProjectRequestData::clear()
{
    B_D(TCompileTexProjectRequestData);
    d->codec = 0;
    d->commands.clear();
    d->compiler = TTexCompiler();
    d->dvipsEnabled = false;
    d->makeindexEnabled = false;
    d->options.clear();
    d->project.clear();
}

QTextCodec *TCompileTexProjectRequestData::codec() const
{
    return d_func()->codec;
}

QStringList TCompileTexProjectRequestData::commands() const
{
    return d_func()->commands;
}

TTexCompiler TCompileTexProjectRequestData::compiler() const
{
    return d_func()->compiler;
}

bool TCompileTexProjectRequestData::dvipsEnabled() const
{
    return d_func()->dvipsEnabled;
}

bool TCompileTexProjectRequestData::isValid() const
{
    const B_D(TCompileTexProjectRequestData);
    return d->codec && d->compiler.isValid();
}

bool TCompileTexProjectRequestData::makeindexEnabled() const
{
    return d_func()->makeindexEnabled;
}

QStringList TCompileTexProjectRequestData::options() const
{
    return d_func()->options;
}

TTexProject TCompileTexProjectRequestData::project() const
{
    return d_func()->project;
}

void TCompileTexProjectRequestData::setCodec(QTextCodec *codec)
{
    d_func()->codec = codec;
}

void TCompileTexProjectRequestData::setCommands(const QStringList &commands)
{
    d_func()->commands = commands;
}

void TCompileTexProjectRequestData::setCompiler(const TTexCompiler &compiler)
{
    d_func()->compiler = compiler;
}

void TCompileTexProjectRequestData::setDvipsEnabled(bool enabled)
{
    d_func()->dvipsEnabled = enabled;
}

void TCompileTexProjectRequestData::setMakeindexEnabled(bool enabled)
{
    d_func()->makeindexEnabled = enabled;
}

void TCompileTexProjectRequestData::setOptions(const QStringList &options)
{
    d_func()->options = options;
}

void TCompileTexProjectRequestData::setProject(const TTexProject &project)
{
    d_func()->project = project;
}

/*============================== Public operators ==========================*/

TCompileTexProjectRequestData &TCompileTexProjectRequestData::operator =(const TCompileTexProjectRequestData &other)
{
    B_D(TCompileTexProjectRequestData);
    const TCompileTexProjectRequestDataPrivate *dd = other.d_func();
    d->codec = dd->codec;
    d->commands = dd->commands;
    d->compiler = dd->compiler;
    d->dvipsEnabled = dd->dvipsEnabled;
    d->makeindexEnabled = dd->makeindexEnabled;
    d->options = dd->options;
    d->project = dd->project;
    return *this;
}

bool TCompileTexProjectRequestData::operator ==(const TCompileTexProjectRequestData &other) const
{
    const B_D(TCompileTexProjectRequestData);
    const TCompileTexProjectRequestDataPrivate *dd = other.d_func();
    return d->codec == dd->codec && d->commands == dd->commands && d->compiler == dd->compiler
            && d->dvipsEnabled == dd->dvipsEnabled && d->makeindexEnabled == dd->makeindexEnabled
            && d->options == dd->options && d->project == dd->project;
}

bool TCompileTexProjectRequestData::operator !=(const TCompileTexProjectRequestData &other) const
{
    return !(*this == other);
}

TCompileTexProjectRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCompileTexProjectRequestData &data)
{
    const TCompileTexProjectRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream << m;
    m.insert("codec_name", d->codec ? d->codec->name() : QByteArray());
    m.insert("commands", d->commands);
    m.insert("compiler", d->compiler);
    m.insert("dvips_enabled", d->dvipsEnabled);
    m.insert("makeindex_enabled", d->makeindexEnabled);
    m.insert("options", d->options);
    m.insert("project", d->project);
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompileTexProjectRequestData &data)
{
    TCompileTexProjectRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->codec = QTextCodec::codecForName(m.value("codec_name").toByteArray());
    d->commands = m.value("commands").toStringList();
    d->compiler = m.value("compiler").value<TTexCompiler>();
    d->dvipsEnabled = m.value("dvips_enabled").toBool();
    d->makeindexEnabled = m.value("makeindex_enabled").toBool();
    d->options = m.value("options").toStringList();
    d->project = m.value("project").value<TTexProject>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompileTexProjectRequestData &/*data*/)
{
    //const TCompileTexProjectRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TCompileTexProjectRequestData(" << ")";
    return dbg.space();
}
