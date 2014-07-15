#include "tproject.h"

#include "tbinaryfile.h"
#include "tbinaryfilelist.h"

#include <BBase>
#include <BDirTools>
#include <BeQtCore/private/bbase_p.h>
#include <BTextTools>

#include <QDataStream>
#include <QDebug>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TProjectPrivate =============================
============================================================================*/

class TProjectPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TProject)
public:
    TBinaryFileList files;
    TBinaryFile mainFile;
public:
    explicit TProjectPrivate(TProject *q);
    ~TProjectPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TProjectPrivate)
};

/*============================================================================
================================ TProjectPrivate =============================
============================================================================*/

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

/*============================== Public constructors =======================*/

TProject::TProject() :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
}

TProject::TProject(const QString &dir, const QString &relativeMainFileName,
                         const QStringList &relativeFileNames) :
    BBase(*new TProjectPrivate(this))
{
    d_func()->init();
    load(dir, relativeMainFileName, relativeFileNames);
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
    d->mainFile.clear();
    d->files.clear();
}

bool TProject::isValid() const
{
    if (!d_func()->mainFile.isValid())
        return false;
    foreach (const TBinaryFile &f, d_func()->files) {
        if (!f.isValid())
            return false;
    }
    return true;
}

bool TProject::load(const QString &dir, const QString &relativeMainFileName, QStringList relativeFileNames)
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
    B_D(TProject);
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

bool TProject::mayBeExecutable() const
{
    return d_func()->mainFile.mayBeExecutable();
}

bool TProject::save(const QString &dir) const
{
    if (!isValid() || dir.isEmpty() || !d_func()->mainFile.save(dir))
        return false;
    foreach (const TBinaryFile &f, d_func()->files) {
        if (!f.save(dir))
            return false;
    }
    return true;
}

int TProject::size() const
{
    if (!isValid())
        return 0;
    int sz = d_func()->mainFile.size();
    foreach (const TBinaryFile &f, d_func()->files)
        sz += f.size();
    return sz;
}

/*============================== Public operators ==========================*/

TProject &TProject::operator =(const TProject &other)
{
    B_D(TProject);
    const TProjectPrivate *dd = other.d_func();
    d->mainFile = dd->mainFile;
    d->files = dd->files;
    return *this;
}

bool TProject::operator ==(const TProject &other) const
{
    const B_D(TProject);
    const TProjectPrivate *dd = other.d_func();
    return d->mainFile == dd->mainFile && d->files == dd->files;
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
    m.insert("main_file", d->mainFile);
    m.insert("files", d->files);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TProject &project)
{
    TProjectPrivate *d = project.d_func();
    QVariantMap m;
    stream >> m;
    d->mainFile = m.value("main_file").value<TBinaryFile>();
    d->files = m.value("files").value<TBinaryFileList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TProject &project)
{
    dbg.nospace() << "TProject(" << project.size() << ")";
    return dbg.space();
}
