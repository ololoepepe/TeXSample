#include "ttexproject.h"
#include "tglobal.h"
#include "tprojectfile.h"
#include "tprojectfilelist.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BDirTools>
#include <BeQt>
#include <BTextTools>

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
#include <QVariantMap>

/*============================================================================
================================ TTexProjectPrivate ==========================
============================================================================*/

class TTexProjectPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TTexProject)
public:
    static QStringList dependencies(const QString &text, const QString &path, QTextCodec *codec = 0, bool *ok = 0);
    static QStringList dependencies(const QString &text, const QString &path, const QString &codecName, bool *ok = 0);
public:
    explicit TTexProjectPrivate(TTexProject *q);
    ~TTexProjectPrivate();
public:
    void init();
public:
    TProjectFile rootFile;
    TProjectFileList files;
private:
    Q_DISABLE_COPY(TTexProjectPrivate)
};

/*============================================================================
================================ TTexProjectPrivate ==========================
============================================================================*/

/*============================== Static public methods =====================*/

QStringList TTexProjectPrivate::dependencies(const QString &text, const QString &path, QTextCodec *codec, bool *ok)
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
    QStringList list = TProjectFile::externalFiles(text, &bok);
    if (!bok)
        return bRet(ok, false, list);
    foreach (int i, bRangeR(list.size() - 1, 0))
        list[i].prepend(path + "/");
    foreach (const QString &fn, list)
    {
        if (QFileInfo(fn).suffix().compare("tex", Qt::CaseInsensitive))
            continue;
        bok = false;
        QStringList xlist = TProjectFile::externalFiles(fn, codec, &bok);
        if (!bok)
            return bRet(ok, false, list);
        list << xlist;
    }
    BTextTools::removeDuplicates(&list, cs);
    BTextTools::sortComprising(&list, cs);
    return bRet(ok, true, list);
}

QStringList TTexProjectPrivate::dependencies(const QString &text, const QString &path, const QString &codecName,
                                             bool *ok)
{
    return dependencies(text, path, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() :
                                                                                    QByteArray("UTF-8")), ok);
}

/*============================== Public constructors =======================*/

TTexProjectPrivate::TTexProjectPrivate(TTexProject *q) :
    BBasePrivate(q)
{
    //
}

TTexProjectPrivate::~TTexProjectPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TTexProjectPrivate::init()
{
    //
}

/*============================================================================
================================ TTexProject =================================
============================================================================*/

/*============================== Static public methods =====================*/

int TTexProject::size(const QString &rootFilePath, QTextCodec *codec, bool sourceOnly)
{
    return size(rootFilePath, codec ? QString(codec->name()) : QString("UTF-8"), sourceOnly);
}

int TTexProject::size(const QString &rootFilePath, const QString &codecName, bool sourceOnly)
{
    if (rootFilePath.isEmpty())
        return -1;
    QString cn = !codecName.isEmpty() ? codecName : QString("UTF-8");
    bool ok = false;
    QString text = BDirTools::readTextFile(rootFilePath, cn, &ok);
    if (!ok)
        return -1;
    ok = false;
    QFileInfo fi(rootFilePath);
    QString path = fi.path();
    QString bn = fi.baseName();
    QStringList list = TTexProjectPrivate::dependencies(text, path, cn, &ok);
    if (!ok)
        return -1;
    int sz = fi.size() * 2;
    foreach (const QString &fn, list)
    {
        static const QStringList suffixes = QStringList() << "tex" << "pic";
        if (suffixes.contains(QFileInfo(fn).suffix().toLower()))
            sz += 2 * QFileInfo(fn).size();
        else
            sz += QFileInfo(fn).size();
    }
    if (!sourceOnly)
    {
        QFileInfo fi(path + "/" + bn + ".pdf");
        if (fi.isFile())
            sz += fi.size();
    }
    return sz;
}

/*============================== Public constructors =======================*/

TTexProject::TTexProject() :
    BBase(*new TTexProjectPrivate(this))
{
    d_func()->init();
}

TTexProject::TTexProject(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec) :
    BBase(*new TTexProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, rootFileText, codec);
}

TTexProject::TTexProject(const QString &rootFileName, const QString &rootFileText, const QString &codecName) :
    BBase(*new TTexProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, rootFileText, codecName);
}

TTexProject::TTexProject(const QString &rootFileName, QTextCodec *codec) :
    BBase(*new TTexProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, codec);
}

TTexProject::TTexProject(const QString &rootFileName, const QString &codecName) :
    BBase(*new TTexProjectPrivate(this))
{
    d_func()->init();
    load(rootFileName, codecName);
}

TTexProject::TTexProject(const TTexProject &other) :
    BBase(*new TTexProjectPrivate(this))
{
    d_func()->init();
    *this = other;
}

TTexProject::~TTexProject()
{
    //
}

/*============================== Public methods ============================*/

void TTexProject::clear()
{
    B_D(TTexProject);
    d->rootFile.clear();
    d->files.clear();
}

TProjectFile *TTexProject::rootFile()
{
    return &d_func()->rootFile;
}

const TProjectFile *TTexProject::rootFile() const
{
    return &d_func()->rootFile;
}

QList<TProjectFile> *TTexProject::files()
{
    return &d_func()->files;
}

const QList<TProjectFile> *TTexProject::files() const
{
    return &d_func()->files;
}

QString TTexProject::rootFileName() const
{
    return d_func()->rootFile.fileName();
}

QStringList TTexProject::externalFiles(bool *ok) const
{
    bool bok = false;
    QStringList list = rootFile()->externalFiles(&bok);
    if (!bok)
        bRet(ok, false, list);
    foreach (const TProjectFile &pf, d_func()->files)
    {
        list << pf.externalFiles(&bok);
        if (!bok)
            bRet(ok, false, list);
    }
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive)
    {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    BTextTools::removeDuplicates(&list, cs);
    BTextTools::sortComprising(&list, cs);
    return bRet(ok, true, list);
}

QStringList TTexProject::restrictedCommands() const
{
    QStringList list = d_func()->rootFile.restrictedCommands();
    foreach (const TProjectFile &f, d_func()->files)
        list << f.restrictedCommands();
    list.removeDuplicates();
    return list;
}

void TTexProject::removeRestrictedCommands()
{
    d_func()->rootFile.removeRestrictedCommands();
    foreach (int i, bRangeD(0, d_func()->files.size() - 1))
        d_func()->files[i].removeRestrictedCommands();
}

bool TTexProject::prependExternalFileNames(const QString &subdir)
{
    if (!d_func()->rootFile.prependExternalFileNames(subdir))
        return false;
    foreach (int i, bRangeD(0, d_func()->files.size() - 1))
        if (!d_func()->files[i].prependExternalFileNames(subdir))
            return false;
    return true;
}

void TTexProject::replace(const QString &oldString, const QString &newString, Qt::CaseSensitivity cs)
{
    B_D(TTexProject);
    d->rootFile.setText(d->rootFile.text().replace(oldString, newString, cs));
    foreach (int i, bRangeD(0, d->files.size() - 1))
        d->files[i].setText(d->files.at(i).text().replace(oldString, newString, cs));
}

bool TTexProject::load(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec)
{
    return load(rootFileName, rootFileText, codec ? QString(codec->name()) : QString("UTF-8"));
}

bool TTexProject::load(const QString &rootFileName, const QString &rootFileText, const QString &codecName)
{
    clear();
    if (rootFileName.isEmpty() || rootFileText.isEmpty())
        return false;
    B_D(TTexProject);
    QString cn = !codecName.isEmpty() ? codecName : QString("UTF-8");
    QString path = QFileInfo(rootFileName).path();
    d->rootFile.setFileName(rootFileName);
    d->rootFile.setText(rootFileText);
    bool ok = false;
    QStringList list = TTexProjectPrivate::dependencies(rootFileText, QFileInfo(rootFileName).path(), cn, &ok);
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
        TProjectFile f(fn, text ? TProjectFile::Text : TProjectFile::Binary, cn, subdir);
        if (!f.isValid())
        {
            clear();
            return false;
        }
        d->files << f;
    }
    return true;
}

bool TTexProject::load(const QString &rootFileName, QTextCodec *codec)
{
    return load(rootFileName, codec ? QString(codec->name()) : QString("UTF-8"));
}

bool TTexProject::load(const QString &rootFileName, const QString &codecName)
{
    clear();
    bool ok = false;
    QString text = BDirTools::readTextFile(rootFileName, codecName, &ok);
    return ok && load(rootFileName, text, codecName);
}

bool TTexProject::save(const QString &dir, QTextCodec *codec) const
{
    if (!isValid() || dir.isEmpty() || !rootFile()->save(dir, codec))
        return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.save(dir, codec))
            return false;
    return true;
}

bool TTexProject::save(const QString &dir, const QString &codecName) const
{
    return save(dir, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() : QByteArray("UTF-8")));
}

bool TTexProject::isValid() const
{
    if (!d_func()->rootFile.isValid())
        return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.isValid())
            return false;
    return true;
}

int TTexProject::size() const
{
    int sz = d_func()->rootFile.size();
    foreach (const TProjectFile &f, d_func()->files)
        sz += f.size();
    return sz;
}

/*============================== Public operators ==========================*/

TTexProject &TTexProject::operator =(const TTexProject &other)
{
    B_D(TTexProject);
    const TTexProjectPrivate *dd = other.d_func();
    d->rootFile = dd->rootFile;
    d->files = dd->files;
    return *this;
}

bool TTexProject::operator ==(const TTexProject &other) const
{
    const B_D(TTexProject);
    const TTexProjectPrivate *dd = other.d_func();
    return d->rootFile == dd->rootFile && d->files == dd->files;
}

TTexProject::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TTexProject &project)
{
    const TTexProjectPrivate *d = project.d_func();
    QVariantMap m;
    m.insert("root_file", d->rootFile);
    m.insert("files", d->files);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TTexProject &project)
{
    TTexProjectPrivate *d = project.d_func();
    QVariantMap m;
    stream >> m;
    d->rootFile = m.value("root_file").value<TProjectFile>();
    d->files = m.value("files").value<TProjectFileList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TTexProject &project)
{
    dbg.nospace() << "TTexProject(" << project.size() << ")";
    return dbg.space();
}