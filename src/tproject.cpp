#include "tproject.h"
#include "tglobal.h"
#include "tprojectfile.h"
#include "ttexttools.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BDirTools>
#include <BeQt>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QList>
#include <QTextCodec>
#include <QStringList>
#include <QFileInfo>
#include <QRegExp>
#include <QDir>

/*============================================================================
================================ TProjectPrivate =============================
============================================================================*/

class TProjectPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TProject)
public:
    static QStringList dependencies(const QString &text, const QString &path, QTextCodec *codec = 0, bool *ok = 0);
    static QStringList dependencies(const QString &text, const QString &path, const QString &codecName, bool *ok = 0);
public:
    explicit TProjectPrivate(TProject *q);
    ~TProjectPrivate();
public:
    void init();
public:
    QString codecName;
    TProjectFile rootFile;
    QList<TProjectFile> files;
private:
    Q_DISABLE_COPY(TProjectPrivate)
};

/*============================================================================
================================ TProjectPrivate =============================
============================================================================*/

/*============================== Static public methods =====================*/

QStringList TProjectPrivate::dependencies(const QString &text, const QString &path, QTextCodec *codec, bool *ok)
{
    if (text.isEmpty() || path.isEmpty() || !QDir(path).exists())
        return bRet(ok, false, QStringList());
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive)
    {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    if (!codec)
        codec = QTextCodec::codecForName("UTF-8");
    bool bok = false;
    QStringList list = TProject::externalFiles(text, &bok);
    if (!bok)
        return bRet(ok, false, list);
    TTextTools::sortComprising(&list, cs);
    foreach (int i, bRangeR(list.size() - 1, 0))
        list[i].prepend(path + "/");
    foreach (const QString &fn, list)
    {
        if (QFileInfo(fn).suffix().compare("tex", Qt::CaseInsensitive))
            continue;
        bok = false;
        QStringList xlist = TProject::externalFiles(fn, codec, &bok);
        if (!bok)
            return bRet(ok, false, list);
        list << xlist;
    }
    TTextTools::removeDuplicates(&list, cs);
    TTextTools::sortComprising(&list, cs);
    return bRet(ok, true, list);
}

QStringList TProjectPrivate::dependencies(const QString &text, const QString &path, const QString &codecName, bool *ok)
{
    return dependencies(text, path, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() :
                                                                                    QByteArray("UTF-8")), ok);
}

/*============================== Public constructors =======================*/

TProjectPrivate::TProjectPrivate(TProject *q) :
    BBasePrivate(q)
{
    //
}

TProjectPrivate::~TProjectPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TProjectPrivate::init()
{
    //
}

/*============================================================================
================================ TProject ====================================
============================================================================*/

/*============================== Static public methods =====================*/

QStringList TProject::externalFiles(const QString &text, bool *ok)
{
    if (text.isEmpty())
        return bRet(ok, true, QStringList());
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive)
    {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    static const QStringList schemes = QStringList() << "http" << "https" << "ftp";
    QRegExp what(".+");
    QRegExp pref("\\s*\\\\includegraphics(\\[.*\\])?\\{");
    QRegExp post("\\}");
    QStringList list = TTextTools::match(text, what, pref, post); // \includegraphics[...]{...}
    pref.setPattern("\\s*\\\\input\\s+");
    post.setPattern("");
    list << TTextTools::match(text, what, pref, post); // \input "..."
    pref.setPattern("\\\\href\\{(run\\:)?");
    post.setPattern("((\\\\)?\\#.+)?\\}\\{.+\\}");
    list << TTextTools::match(text, what, pref, post); // \href{run:...}{...}
    TTextTools::removeDuplicates(&list, cs);
    TTextTools::removeAll(&list, "texsample.tex", cs);
    foreach (int i, bRangeR(list.size() - 1, 0))
    {
        list[i] = BeQt::unwrapped(list.at(i));
        if (QFileInfo(list.at(i)).isAbsolute())
            return bRet(ok, false, list);
        foreach (const QString &s, schemes)
        {
            if (list.at(i).left((s + "://").length()) == s + "://")
            {
                list.removeAt(i);
                break;
            }
        }
    }
    return bRet(ok, true, list);
}

QStringList TProject::externalFiles(const QString &fileName, QTextCodec *codec, bool *ok)
{
    bool bok = false;
    QString text = BDirTools::readTextFile(fileName, codec, &bok);
    if (!bok)
        return bRet(ok, false, QStringList());
    return externalFiles(text, ok);
}

QStringList TProject::externalFiles(const QString &fileName, const QString &codecName, bool *ok)
{
    return externalFiles(fileName, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() :
                                                                                   QByteArray("UTF-8")), ok);
}

/*============================== Public constructors =======================*/

TProject::TProject() :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
}

TProject::TProject(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec) :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, rootFileText, codec);
}

TProject::TProject(const QString &rootFileName, const QString &rootFileText, const QString &codecName) :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, rootFileText, codecName);
}

TProject::TProject(const QString &rootFileName, QTextCodec *codec) :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, codec);
}

TProject::TProject(const QString &rootFileName, const QString &codecName) :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, codecName);
}

TProject::TProject(const TProject &other) :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
    *this = other;
}

TProject::~TProject()
{
    //
}

/*============================== Public methods ============================*/

void TProject::clear()
{
    B_D(TProject);
    d->codecName.clear();
    d->rootFile.clear();
    d->files.clear();
}

QString TProject::codecName() const
{
    return d_func()->codecName;
}

TProjectFile *TProject::rootFile()
{
    return &d_func()->rootFile;
}

const TProjectFile *TProject::rootFile() const
{
    return &d_func()->rootFile;
}

QList<TProjectFile> *TProject::files()
{
    return &d_func()->files;
}

const QList<TProjectFile> *TProject::files() const
{
    return &d_func()->files;
}

bool TProject::load(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec)
{
    return load(rootFileName, rootFileText, codec ? QString(codec->name()) : QString("UTF-8"));
}

bool TProject::load(const QString &rootFileName, const QString &rootFileText, const QString &codecName)
{
    clear();
    if (rootFileName.isEmpty() || rootFileText.isEmpty())
        return false;
    B_D(TProject);
    d->codecName = !codecName.isEmpty() ? codecName : QString("UTF-8");
    QString path = QFileInfo(rootFileName).path();
    d->rootFile.setFileName(rootFileName);
    d->rootFile.setText(rootFileText);
    bool ok = false;
    QStringList list = TProjectPrivate::dependencies(rootFileText, QFileInfo(rootFileName).path(), d->codecName, &ok);
    if (!ok)
    {
        clear();
        return false;
    }
    foreach (const QString &fn, list)
    {
        static const QStringList suffixes = QStringList() << "tex" << "pic";
        bool text = suffixes.contains(QFileInfo(fn).suffix().toLower());
        QString subdir = QFileInfo(fn).path().remove(0, path.length());
        TProjectFile f(fn, text ? TProjectFile::Text : TProjectFile::Binary, d->codecName, subdir);
        if (!f.isValid())
        {
            clear();
            return false;
        }
        d->files << f;
    }
    return true;
}

bool TProject::load(const QString &rootFileName, QTextCodec *codec)
{
    return load(rootFileName, codec ? QString(codec->name()) : QString("UTF-8"));
}

bool TProject::load(const QString &rootFileName, const QString &codecName)
{
    clear();
    bool ok = false;
    QString text = BDirTools::readTextFile(rootFileName, codecName, &ok);
    return ok && load(rootFileName, text, codecName);
}

bool TProject::save(const QString &dir, QTextCodec *codec)
{
    if (!isValid() || dir.isEmpty() || !rootFile()->save(dir, codec))
        return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.save(dir, codec))
            return false;
    return true;
}

bool TProject::save(const QString &dir, const QString &codecName)
{
    return save(dir, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() : QByteArray("UTF-8")));
}

bool TProject::isValid() const
{
    if (!d_func()->rootFile.isValid())
        return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.isValid())
            return false;
    return true;
}

int TProject::size() const
{
    int sz = d_func()->rootFile.size();
    foreach (const TProjectFile &f, d_func()->files)
        sz += f.size();
    return sz;
}

/*============================== Public operators ==========================*/

TProject &TProject::operator =(const TProject &other)
{
    B_D(TProject);
    const TProjectPrivate *dd = other.d_func();
    d->codecName = dd->codecName;
    d->rootFile = dd->rootFile;
    d->files = dd->files;
    return *this;
}

bool TProject::operator ==(const TProject &other) const
{
    const B_D(TProject);
    const TProjectPrivate *dd = other.d_func();
    return !d->codecName.compare(dd->codecName, Qt::CaseInsensitive)
            && d->rootFile == dd->rootFile && d->files == dd->files;
}

TProject::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TProject &project)
{
    const TProjectPrivate *d = project.d_func();
    stream << d->codecName;
    stream << d->rootFile;
    stream << d->files;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TProject &project)
{
    TProjectPrivate *d = project.d_func();
    stream >> d->codecName;
    stream >> d->rootFile;
    stream >> d->files;
    return stream;
}

QDebug operator <<(QDebug dbg, const TProject &project)
{
    const TProjectPrivate *d = project.d_func();
    dbg.nospace() << "TProject(" << d->codecName << "," << project.size() << ")";
    return dbg.space();
}
