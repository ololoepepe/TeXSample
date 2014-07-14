#include "ttexproject.h"

#include "tbinaryfile.h"
#include "tbinaryfilelist.h"
#include "ttexfile.h"
#include "ttexfilelist.h"

#include <BBase>
#include <BDirTools>
#include <BeQt>
#include <BeQtCore/private/bbase_p.h>
#include <BTextTools>

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TTexProjectPrivate ==========================
============================================================================*/

class TTexProjectPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TTexProject)
public:
    TBinaryFileList binaryFiles;
    TTexFile rootFile;
    TTexFileList texFiles;
public:
    explicit TTexProjectPrivate(TTexProject *q);
    ~TTexProjectPrivate();
public:
    bool containsFile(const QString &fileName) const;
    void init();
    bool load(const TTexFile &file, const QString &path, QTextCodec *codec);
private:
    Q_DISABLE_COPY(TTexProjectPrivate)
};

/*============================================================================
================================ TTexProjectPrivate ==========================
============================================================================*/

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

bool TTexProjectPrivate::containsFile(const QString &fileName) const
{
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive) {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    if (!rootFile.fileName().compare(fileName, cs))
        return true;
    foreach (const TTexFile &f, texFiles) {
        if (!f.fileName().compare(fileName, cs))
            return true;
    }
    foreach (const TBinaryFile &f, binaryFiles) {
        if (!f.fileName().compare(fileName, cs))
            return true;
    }
    return false;
}

void TTexProjectPrivate::init()
{
    //
}

bool TTexProjectPrivate::load(const TTexFile &file, const QString &path, QTextCodec *codec)
{
    bool ok = false;
    QStringList list = file.externalFileNames(&ok);
    if (!ok)
        return false;
    foreach (int i, bRangeR(list.size() - 1, 0))
        list[i].prepend(path + "/");
    foreach (const QString &fn, list) {
        if (containsFile(fn))
            continue;
        static const QStringList Suffixes = QStringList() << "tex" << "pic";
        QString subpath = QFileInfo(fn).path().remove(0, path.length());
        if (Suffixes.contains(QFileInfo(fn).suffix().toLower())) {
            TTexFile f(fn, codec, subpath);
            if (!f.isValid())
                return false;
            texFiles << f;
            if (!load(f, path, codec))
                return false;
        } else {
            TBinaryFile f(fn, subpath);
            if (!f.isValid())
                return false;
            binaryFiles << f;
        }
    }
    return true;
}

/*============================================================================
================================ TTexProject =================================
============================================================================*/

/*============================== Public constructors =======================*/

TTexProject::TTexProject() :
    BBase(*new TTexProjectPrivate(this))
{
    d_func()->init();
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

QList<TBinaryFile> &TTexProject::binaryFiles()
{
    return d_func()->binaryFiles;
}

const QList<TBinaryFile> &TTexProject::binaryFiles() const
{
    return d_func()->binaryFiles;
}

void TTexProject::clear()
{
    B_D(TTexProject);
    d->rootFile.clear();
    d->texFiles.clear();
    d->binaryFiles.clear();
}

bool TTexProject::isValid() const
{
    if (!d_func()->rootFile.isValid())
        return false;
    foreach (const TTexFile &f, d_func()->texFiles) {
        if (!f.isValid())
            return false;
    }
    foreach (const TBinaryFile &f, d_func()->binaryFiles) {
        if (!f.isValid())
            return false;
    }
    return true;
}

bool TTexProject::load(const QString &rootFileName, const QString &rootFileText, QTextCodec *codec)
{
    clear();
    if (rootFileName.isEmpty() || rootFileText.isEmpty())
        return false;
    B_D(TTexProject);
    if (!codec)
        codec = QTextCodec::codecForName("UTF-8");
    QString path = QFileInfo(rootFileName).path();
    d->rootFile.setFileName(rootFileName);
    d->rootFile.setText(rootFileText);
    if (!d->load(d->rootFile, path, codec)) {
        clear();
        return false;
    }
    return true;
}

bool TTexProject::load(const QString &rootFileName, QTextCodec *codec)
{
    clear();
    bool ok = false;
    QString text = BDirTools::readTextFile(rootFileName, codec, &ok);
    return ok && load(rootFileName, text, codec);
}

bool TTexProject::prependExternalFileNames(const QString &subdir)
{
    if (!d_func()->rootFile.prependExternalFileNames(subdir))
        return false;
    foreach (int i, bRangeD(0, d_func()->texFiles.size() - 1)) {
        if (!d_func()->texFiles[i].prependExternalFileNames(subdir))
            return false;
    }
    return true;
}

void TTexProject::removeRestrictedCommands()
{
    d_func()->rootFile.removeRestrictedCommands();
    foreach (int i, bRangeD(0, d_func()->texFiles.size() - 1))
        d_func()->texFiles[i].removeRestrictedCommands();
}

QStringList TTexProject::restrictedCommands() const
{
    QStringList list = d_func()->rootFile.restrictedCommands();
    foreach (const TTexFile &f, d_func()->texFiles)
        list << f.restrictedCommands();
    list.removeDuplicates();
    return list;
}

TTexFile &TTexProject::rootFile()
{
    return d_func()->rootFile;
}

const TTexFile &TTexProject::rootFile() const
{
    return d_func()->rootFile;
}

bool TTexProject::save(const QString &dir, QTextCodec *codec) const
{
    if (!isValid() || dir.isEmpty() || !d_func()->rootFile.save(dir, codec))
        return false;
    foreach (const TTexFile &f, d_func()->texFiles) {
        if (!f.save(dir, codec))
            return false;
    }
    foreach (const TBinaryFile &f, d_func()->binaryFiles) {
        if (!f.save(dir))
            return false;
    }
    return true;
}

int TTexProject::size() const
{
    int sz = d_func()->rootFile.size();
    foreach (const TBinaryFile &f, d_func()->binaryFiles)
        sz += f.size();
    foreach (const TTexFile &f, d_func()->texFiles)
        sz += f.size();
    return sz;
}

QList<TTexFile> &TTexProject::texFiles()
{
    return d_func()->texFiles;
}

const QList<TTexFile> &TTexProject::texFiles() const
{
    return d_func()->texFiles;
}

/*============================== Public operators ==========================*/

TTexProject &TTexProject::operator =(const TTexProject &other)
{
    B_D(TTexProject);
    const TTexProjectPrivate *dd = other.d_func();
    d->rootFile = dd->rootFile;
    d->binaryFiles = dd->binaryFiles;
    d->texFiles = dd->texFiles;
    return *this;
}

bool TTexProject::operator ==(const TTexProject &other) const
{
    const B_D(TTexProject);
    const TTexProjectPrivate *dd = other.d_func();
    return d->rootFile == dd->rootFile && d->binaryFiles == dd->binaryFiles && d->texFiles == dd->texFiles;
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
    m.insert("binary_files", d->binaryFiles);
    m.insert("tex_files", d->texFiles);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TTexProject &project)
{
    TTexProjectPrivate *d = project.d_func();
    QVariantMap m;
    stream >> m;
    d->rootFile = m.value("root_file").value<TTexFile>();
    d->binaryFiles = m.value("binary_files").value<TBinaryFileList>();
    d->texFiles = m.value("tex_files").value<TTexFileList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TTexProject &project)
{
    dbg.nospace() << "TTexProject(" << project.size() << ")";
    return dbg.space();
}
