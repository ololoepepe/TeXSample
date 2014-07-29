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

#include "ttexfile.h"

#include <BBase>
#include <BDirTools>
#include <BeQtCore/private/bbase_p.h>
#include <BTextMatch>
#include <BTextMatchList>
#include <BTextTools>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TTexFilePrivate =============================
============================================================================*/

class TTexFilePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TTexFile)
public:
    QString fileName;
    QString subpath;
    QString text;
public:
   explicit TTexFilePrivate(TTexFile *q);
    ~TTexFilePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TTexFilePrivate)
};

/*============================================================================
================================ TTexFilePrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TTexFilePrivate::TTexFilePrivate(TTexFile *q) :
    BBasePrivate(q)
{
    //
}

TTexFilePrivate::~TTexFilePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TTexFilePrivate::init()
{
    //
}

/*============================================================================
================================ TTexFile ====================================
============================================================================*/

/*============================== Public constructors =======================*/

TTexFile::TTexFile(const QString &fileName, QTextCodec *codec, const QString &subpath) :
    BBase(*new TTexFilePrivate(this))
{
    d_func()->init();
    load(fileName, codec, subpath);
}

TTexFile::TTexFile(const TTexFile &other) :
    BBase(*new TTexFilePrivate(this))
{
    d_func()->init();
    *this = other;
}

TTexFile::~TTexFile()
{
    //
}

/*============================== Public methods ============================*/

void TTexFile::clear()
{
    B_D(TTexFile);
    d->fileName.clear();
    d->subpath.clear();
    d->text.clear();
}

QStringList TTexFile::externalFileNames(bool *ok) const
{
    const B_D(TTexFile);
    if (d->text.isEmpty())
        return bRet(ok, true, QStringList());
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive) {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    static const QStringList schemes = QStringList() << "http" << "https" << "ftp";
    QRegExp what(".+");
    QRegExp pref("\\s*\\\\includegraphics(\\[.*\\])?\\{");
    QRegExp post("\\}");
    QStringList list = BTextTools::match(d->text, what, pref, post); // \includegraphics[...]{...}
    pref.setPattern("\\s*\\\\input\\s+");
    post.setPattern("");
    list << BTextTools::match(d->text, QRegExp("\\S+"), pref, post); // \input ...
    pref.setPattern("\\s*\\\\input\\s+\"");
    post.setPattern("\"");
    list << BTextTools::match(d->text, what, pref, post); // \input "..."
    pref.setPattern("\\\\href\\{(run\\:)?");
    post.setPattern("((\\\\)?\\#.+)?\\}\\{.+\\}");
    list << BTextTools::match(d->text, what, pref, post); // \href{run:...}{...}
    foreach (int i, bRangeR(list.size() - 1, 0)) {
        list[i] = BTextTools::unwrapped(list.at(i));
        if (QFileInfo(list.at(i)).isAbsolute())
            return bRet(ok, false, list);
        foreach (const QString &s, schemes) {
            if (list.at(i).left((s + "://").length()) == s + "://") {
                list.removeAt(i);
                break;
            }
        }
    }
    BTextTools::removeDuplicates(&list, cs);
    BTextTools::removeAll(&list, "texsample.tex", cs);
    BTextTools::sortComprising(&list, cs);
    return bRet(ok, true, list);
}

QString TTexFile::fileName() const
{
    return d_func()->fileName;
}

bool TTexFile::isValid() const
{
    return !d_func()->fileName.isEmpty() && !d_func()->text.isEmpty();
}

bool TTexFile::load(const QString &fileName, QTextCodec *codec, const QString &subpath)
{
    bool ok = false;
    d_func()->text = BDirTools::readTextFile(fileName, codec ? codec : QTextCodec::codecForName("UTF-8"), &ok);
    if (!ok) {
        clear();
        return false;
    }
    setFileName(fileName);
    d_func()->subpath = subpath;
    return ok;
}

bool TTexFile::prependExternalFileNames(const QString &subpath)
{
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive) {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    if (subpath.isEmpty() || !isValid())
        return false;
    B_D(TTexFile);
    if (d->text.isEmpty())
        return true;
    bool ok = false;
    QStringList files = externalFileNames(&ok);
    if(!ok)
        return false;
    QString text = d->text;
    foreach (const QString fn, files)
        text.replace(fn, subpath + "/" + fn, cs);
    BTextMatchList list = BTextTools::match(text, QRegExp(".+"), QRegExp("\\s*\\\\input\\s+"));
    foreach (const BTextMatch &r, list) {
        QString txt = r.text();
        if (txt.left(1) != "\"") {
            if (txt.right(1) != "\"")
                text.replace(r.position(), r.length(), txt.prepend("\"").append("\""));
            else
                return false;
        }
    }
    d->text = text;
    return true;
}

QString TTexFile::relativeFileName() const
{
    if (!isValid())
        return "";
    return d_func()->subpath + (!d_func()->subpath.isEmpty() ? "/" : "") + d_func()->fileName;
}

void TTexFile::removeRestrictedCommands()
{
    if (!isValid())
        return;
    B_D(TTexFile);
    if (d->text.isEmpty())
        return;
    QStringList sl = d->text.split('\n');
    static const QRegExp Rx = QRegExp("\\s*\\\\(documentclass|usepackage|makeindex|"
                                      "input\\s+texsample\\.tex|(begin|end)\\{document\\}).*");
    foreach (int i, bRangeD(0, sl.size() - 1))
        sl[i].remove(Rx);
    d->text = sl.join("\n");
}

QStringList TTexFile::restrictedCommands() const
{
    const B_D(TTexFile);
    QStringList list;
    if (d->text.isEmpty())
        return list;
    if (d->text.contains(QRegExp("\\s*\\\\documentclass")))
        list << "\\documentclass";
    if (d->text.contains(QRegExp("\\s*\\\\usepackage")))
        list << "\\usepackage";
    if (d->text.contains(QRegExp("\\s*\\\\makeindex")))
        list << "\\makeindex";
    if (d->text.contains(QRegExp("\\s*\\\\input\\s+texsample\\.tex")))
        list << "\\input texsample.tex";
    if (d->text.contains(QRegExp("\\s*\\begin\\{document\\}")))
        list << "\\begin{document}";
    if (d->text.contains(QRegExp("\\s*\\end\\{document\\}")))
        list << "\\end{document}";
    return list;
}

bool TTexFile::save(const QString &dir, QTextCodec *codec) const
{
    if (!isValid() || dir.isEmpty())
        return false;
    const B_D(TTexFile);
    QString fn = dir + (!d->subpath.isEmpty() ? ("/" + d->subpath) : QString()) + "/" + d->fileName;
    return BDirTools::writeTextFile(fn, d->text, codec ? codec : QTextCodec::codecForName("UTF-8"));
}

void TTexFile::setFileName(const QString &fileName)
{
    d_func()->fileName = !fileName.isEmpty() ? QFileInfo(fileName).fileName() : QString();
}

void TTexFile::setRelativeFileName(const QString &relativeFileName)
{
    int ind = relativeFileName.lastIndexOf('/');
    if (ind < 0) {
        d_func()->fileName = relativeFileName;
        d_func()->subpath.clear();
        return;
    }
    d_func()->fileName = relativeFileName.mid(ind + 1);
    d_func()->subpath = relativeFileName.left(ind);
}

void TTexFile::setSubpath(const QString &subpath)
{
    d_func()->subpath = subpath;
}

void TTexFile::setText(const QString &text)
{
    d_func()->text = text;
}

int TTexFile::size() const
{
    return d_func()->text.length() * 2;
}

QString TTexFile::subpath() const
{
    return d_func()->subpath;
}

QString TTexFile::text() const
{
    return d_func()->text;
}

/*============================== Public operators ==========================*/

TTexFile &TTexFile::operator =(const TTexFile &other)
{
    B_D(TTexFile);
    const TTexFilePrivate *dd = other.d_func();
    d->fileName = dd->fileName;
    d->subpath = dd->subpath;
    d->text = dd->text;
    return *this;
}

bool TTexFile::operator ==(const TTexFile &other) const
{
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive) {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    const B_D(TTexFile);
    const TTexFilePrivate *dd = other.d_func();
    return !d->fileName.compare(dd->fileName, cs) && !d->subpath.compare(dd->subpath, cs)
            && !d->text.compare(dd->text);
}

TTexFile::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TTexFile &file)
{
    const TTexFilePrivate *d = file.d_func();
    QVariantMap m;
    m.insert("file_name", d->fileName);
    m.insert("subpath", d->subpath);
    m.insert("text", d->text);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TTexFile &file)
{
    TTexFilePrivate *d = file.d_func();
    QVariantMap m;
    stream >> m;
    d->fileName = m.value("file_name").toString();
    d->subpath = m.value("subpath").toString();
    d->text = m.value("text").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TTexFile &file)
{
    const TTexFilePrivate *d = file.d_func();
    dbg.nospace() << "TTexFile(" << d->fileName << ")";
    return dbg.space();
}
