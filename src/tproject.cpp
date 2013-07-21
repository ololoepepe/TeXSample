#include "tproject.h"
#include "tglobal.h"
#include "tprojectfile.h"
#include "ttexttools.h"
#include "tprojectfilelist.h"

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
#include <QVariantMap>

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
    TProjectFile rootFile;
    TProjectFileList files;
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

int TProject::size(const QString &rootFilePath, QTextCodec *codec, bool sourceOnly)
{
    return size(rootFilePath, codec ? QString(codec->name()) : QString("UTF-8"), sourceOnly);
}

int TProject::size(const QString &rootFilePath, const QString &codecName, bool sourceOnly)
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
    QStringList list = TProjectPrivate::dependencies(text, path, cn, &ok);
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
    d->rootFile.clear();
    d->files.clear();
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

QString TProject::rootFileName() const
{
    return d_func()->rootFile.fileName();
}

QStringList TProject::externalFiles(bool *ok) const
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
    TTextTools::removeDuplicates(&list, cs);
    TTextTools::sortComprising(&list, cs);
    return bRet(ok, true, list);
}

QStringList TProject::restrictedCommands() const
{
    QStringList list = d_func()->rootFile.restrictedCommands();
    foreach (const TProjectFile &f, d_func()->files)
        list << f.restrictedCommands();
    list.removeDuplicates();
    return list;
}

void TProject::removeRestrictedCommands()
{
    d_func()->rootFile.removeRestrictedCommands();
    foreach (int i, bRangeD(0, d_func()->files.size() - 1))
        d_func()->files[i].removeRestrictedCommands();
}

bool TProject::prependExternalFileNames(const QString &subdir)
{
    if (!d_func()->rootFile.prependExternalFileNames(subdir))
        return false;
    foreach (int i, bRangeD(0, d_func()->files.size() - 1))
        if (!d_func()->files[i].prependExternalFileNames(subdir))
            return false;
    return true;
}

void TProject::replace(const QString &oldString, const QString &newString, Qt::CaseSensitivity cs)
{
    B_D(TProject);
    d->rootFile.setText(d->rootFile.text().replace(oldString, newString, cs));
    foreach (int i, bRangeD(0, d->files.size() - 1))
        d->files[i].setText(d->files.at(i).text().replace(oldString, newString, cs));
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
    QString cn = !codecName.isEmpty() ? codecName : QString("UTF-8");
    QString path = QFileInfo(rootFileName).path();
    d->rootFile.setFileName(rootFileName);
    d->rootFile.setText(rootFileText);
    bool ok = false;
    QStringList list = TProjectPrivate::dependencies(rootFileText, QFileInfo(rootFileName).path(), cn, &ok);
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

bool TProject::save(const QString &dir, QTextCodec *codec) const
{
    if (!isValid() || dir.isEmpty() || !rootFile()->save(dir, codec))
        return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.save(dir, codec))
            return false;
    return true;
}

bool TProject::save(const QString &dir, const QString &codecName) const
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
    d->rootFile = dd->rootFile;
    d->files = dd->files;
    return *this;
}

bool TProject::operator ==(const TProject &other) const
{
    const B_D(TProject);
    const TProjectPrivate *dd = other.d_func();
    return d->rootFile == dd->rootFile && d->files == dd->files;
}

TProject::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TProject &project)
{
    const TProjectPrivate *d = project.d_func();
    QVariantMap m;
    m.insert("root_file", d->rootFile);
    m.insert("files", d->files);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TProject &project)
{
    TProjectPrivate *d = project.d_func();
    QVariantMap m;
    stream >> m;
    d->rootFile = m.value("root_file").value<TProjectFile>();
    d->files = m.value("files").value<TProjectFileList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TProject &project)
{
    dbg.nospace() << "TProject(" << project.size() << ")";
    return dbg.space();
}
