#include "tlabproject.h"
#include "tglobal.h"
#include "tprojectfile.h"
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
#include <QUrl>
#include <QVariantMap>

/*============================================================================
================================ TLabProjectPrivate ==========================
============================================================================*/

class TLabProjectPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLabProject)
public:
    explicit TLabProjectPrivate(TLabProject *q);
    ~TLabProjectPrivate();
public:
    void init();
    bool loadRec(const QString &rootDir, const QString &subdir);
public:
    TProjectFile mainFile;
    TProjectFileList files;
private:
    Q_DISABLE_COPY(TLabProjectPrivate)
};

/*============================================================================
================================ TLabProjectPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TLabProjectPrivate::TLabProjectPrivate(TLabProject *q) :
    BBasePrivate(q)
{
    //
}

TLabProjectPrivate::~TLabProjectPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLabProjectPrivate::init()
{
    //
}

bool TLabProjectPrivate::loadRec(const QString &rootDir, const QString &subdir)
{
    QDir d(rootDir + "/" + subdir);
    foreach (const QString &fn, d.entryList(QDir::Files))
    {
        QString fnn = d.absoluteFilePath(fn);
        if (d.absoluteFilePath(mainFile.fileName()) == fnn)
            continue;
        TProjectFile pf(fnn, TProjectFile::Binary, 0, subdir);
        if (!pf.isValid())
            return false;
        files << pf;
    }
    foreach (const QString &dn, d.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        if (!loadRec(rootDir, subdir + "/" + dn))
            return false;
    return true;
}

/*============================================================================
================================ CProject ====================================
============================================================================*/

/*============================== Public constructors =======================*/

TLabProject::TLabProject() :
    BBase(*new TLabProjectPrivate(this))
{
    d_func()->init();
}

TLabProject::TLabProject(const QString &dir, const QString &mainFileName) :
    BBase(*new TLabProjectPrivate(this))
{
    d_func()->init();
    load(dir, mainFileName);
}

TLabProject::TLabProject(const TLabProject &other) :
    BBase(*new TLabProjectPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLabProject::~TLabProject()
{
    //
}

/*============================== Public methods ============================*/

void TLabProject::clear()
{
    B_D(TLabProject);
    d->mainFile.clear();
    d->files.clear();
}

QString TLabProject::mainFileName() const
{
    return d_func()->mainFile.fileName();
}

bool TLabProject::load(const QString &dir, const QString &mainFileName)
{
    clear();
    if (dir.isEmpty())
        return false;
    B_D(TLabProject);
    QString t = mainFileName;
    QFileInfo fi(dir + "/" + t.remove(dir + "/"));
    QString subdir = fi.path().remove(dir);
    if (!d->mainFile.loadAsBinary(fi.filePath(), subdir))
        return false;
    foreach (const QString &fn, BDirTools::entryList(dir, QDir::Files))
    {
        TProjectFile pf(fn, TProjectFile::Binary);
        if (!pf.isValid())
        {
            clear();
            return false;
        }
        d->files << pf;
    }
    foreach (const QString &dn, QDir(dir).entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        if (!d->loadRec(dir, dn))
        {
            clear();
            return false;
        }
    }
    return true;
}

bool TLabProject::save(const QString &dir) const
{
    if (!isValid() || dir.isEmpty() || !d_func()->mainFile.save(dir))
        return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.save(dir))
            return false;
    return true;
}

bool TLabProject::isValid() const
{
    if (!d_func()->mainFile.isValid() || !d_func()->mainFile.size())
            return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.isValid())
            return false;
    return true;
}

int TLabProject::size() const
{
    if (!isValid())
        return 0;
    int sz = d_func()->mainFile.size();
    foreach (const TProjectFile &f, d_func()->files)
        sz += f.size();
    return sz;
}

/*============================== Public operators ==========================*/

TLabProject &TLabProject::operator =(const TLabProject &other)
{
    B_D(TLabProject);
    const TLabProjectPrivate *dd = other.d_func();
    d->mainFile = dd->mainFile;
    d->files = dd->files;
    return *this;
}

bool TLabProject::operator ==(const TLabProject &other) const
{
    const B_D(TLabProject);
    const TLabProjectPrivate *dd = other.d_func();
    return d->mainFile == dd->mainFile && d->files == dd->files;
}

TLabProject::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLabProject &project)
{
    const TLabProjectPrivate *d = project.d_func();
    QVariantMap m;
    m.insert("main_file", d->mainFile);
    m.insert("files", d->files);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLabProject &project)
{
    TLabProjectPrivate *d = project.d_func();
    QVariantMap m;
    stream >> m;
    d->mainFile = m.value("main_file").value<TProjectFile>();
    d->files = m.value("files").value<TProjectFileList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabProject &project)
{
    dbg.nospace() << "TLabProject(" << project.size() << ")";
    return dbg.space();
}
