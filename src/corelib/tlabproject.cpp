#include "tlabproject.h"

#include "tbinaryfile.h"
#include "tbinaryfilelist.h"

#include <BBase>
#include <BDirTools>
#include <BeQtCore/private/bbase_p.h>
#include <BTextTools>

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QUrl>
#include <QVariant>
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
public:
    TBinaryFileList files;
    TBinaryFile mainFile;
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

/*============================================================================
================================ CProject ====================================
============================================================================*/

/*============================== Public constructors =======================*/

TLabProject::TLabProject() :
    BBase(*new TLabProjectPrivate(this))
{
    d_func()->init();
}

TLabProject::TLabProject(const QString &dir, const QString &relativeMainFileName,
                         const QStringList &relativeFileNames) :
    BBase(*new TLabProjectPrivate(this))
{
    d_func()->init();
    load(dir, relativeMainFileName, relativeFileNames);
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

bool TLabProject::isValid() const
{
    if (!d_func()->mainFile.isValid())
        return false;
    foreach (const TBinaryFile &f, d_func()->files) {
        if (!f.isValid())
            return false;
    }
    return true;
}

bool TLabProject::load(const QString &dir, const QString &relativeMainFileName, QStringList relativeFileNames)
{
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive) {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    clear();
    if (dir.isEmpty() || relativeMainFileName.isEmpty())
        return false;
    relativeFileNames.removeAll("");
    BTextTools::removeDuplicates(relativeFileNames, cs);
    BTextTools::removeAll(relativeFileNames, relativeMainFileName, cs);
    B_D(TLabProject);
    if (!d->mainFile.load(dir + "/" + relativeMainFileName, QFileInfo(relativeMainFileName).path())) {
        clear();
        return false;
    }
    foreach (const QString &fn, relativeFileNames) {
        TBinaryFile f(dir + "/" + fn, QFileInfo(fn).path());
        if (!f.isValid()) {
            clear();
            return false;
        }
        d->files << f;
    }
    return true;
}

bool TLabProject::mayBeExecutable() const
{
    return d_func()->mainFile.mayBeExecutable();
}

bool TLabProject::save(const QString &dir) const
{
    if (!isValid() || dir.isEmpty() || !d_func()->mainFile.save(dir))
        return false;
    foreach (const TBinaryFile &f, d_func()->files) {
        if (!f.save(dir))
            return false;
    }
    return true;
}

int TLabProject::size() const
{
    if (!isValid())
        return 0;
    int sz = d_func()->mainFile.size();
    foreach (const TBinaryFile &f, d_func()->files)
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
    d->mainFile = m.value("main_file").value<TBinaryFile>();
    d->files = m.value("files").value<TBinaryFileList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabProject &project)
{
    dbg.nospace() << "TLabProject(" << project.size() << ")";
    return dbg.space();
}
