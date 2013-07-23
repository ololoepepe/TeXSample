#include "tcompiledproject.h"
#include "tglobal.h"
#include "tprojectfile.h"
#include "ttexttools.h"
#include "tprojectfilelist.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QList>
#include <QStringList>
#include <QDir>
#include <QVariantMap>

/*============================================================================
================================ TCompiledProjectPrivate =====================
============================================================================*/

class TCompiledProjectPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCompiledProject)
public:
    explicit TCompiledProjectPrivate(TCompiledProject *q);
    ~TCompiledProjectPrivate();
public:
    void init();
public:
    TProjectFileList files;
private:
    Q_DISABLE_COPY(TCompiledProjectPrivate)
};

/*============================================================================
================================ TCompiledProjectPrivate =====================
============================================================================*/

/*============================== Public constructors =======================*/

TCompiledProjectPrivate::TCompiledProjectPrivate(TCompiledProject *q) :
    BBasePrivate(q)
{
    //
}

TCompiledProjectPrivate::~TCompiledProjectPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCompiledProjectPrivate::init()
{
    //
}

/*============================================================================
================================ TCompiledProject ============================
============================================================================*/

/*============================== Public constructors =======================*/

TCompiledProject::TCompiledProject(const QString &dir, const QStringList &nameFilters) :
    BBase(*new TCompiledProjectPrivate(this))
{
    d_func()->init();
    load(dir, nameFilters);
}

TCompiledProject::TCompiledProject(const QStringList &files) :
    BBase(*new TCompiledProjectPrivate(this))
{
    d_func()->init();
    load(files);
}

TCompiledProject::TCompiledProject(const TCompiledProject &other) :
    BBase(*new TCompiledProjectPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCompiledProject::~TCompiledProject()
{
    //
}

/*============================== Public methods ============================*/

void TCompiledProject::clear()
{
    B_D(TCompiledProject);
    d->files.clear();
}

QList<TProjectFile> *TCompiledProject::files()
{
    return &d_func()->files;
}

const QList<TProjectFile> *TCompiledProject::files() const
{
    return &d_func()->files;
}

bool TCompiledProject::load(const QString &dir, const QStringList &nameFilters)
{
    if (dir.isEmpty())
        return false;
    QDir d(dir);
    QStringList files = !nameFilters.isEmpty() ? d.entryList(nameFilters, QDir::Files) : d.entryList(QDir::Files);
    foreach (int i, bRangeD(0, files.size() - 1))
        files[i].prepend(dir + "/");
    return load(files);
}

bool TCompiledProject::load(const QStringList &files)
{
    clear();
    if (files.isEmpty())
        return false;
    foreach (const QString &fn, files)
    {
        TProjectFile f(fn, TProjectFile::Binary);
        if (!f.isValid())
        {
            clear();
            return false;
        }
        d_func()->files << f;
    }
    return true;
}

bool TCompiledProject::save(const QString &dir) const
{
    if (!isValid() || dir.isEmpty())
        return false;
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.save(dir))
            return false;
    return true;
}

bool TCompiledProject::isEmpty() const
{
    return d_func()->files.isEmpty();
}

bool TCompiledProject::isValid() const
{
    foreach (const TProjectFile &f, d_func()->files)
        if (!f.isValid())
            return false;
    return true;
}

int TCompiledProject::size() const
{
    int sz = 0;
    foreach (const TProjectFile &f, d_func()->files)
        sz += f.size();
    return sz;
}

/*============================== Public operators ==========================*/

TCompiledProject &TCompiledProject::operator =(const TCompiledProject &other)
{
    d_func()->files = other.d_func()->files;
    return *this;
}

bool TCompiledProject::operator ==(const TCompiledProject &other) const
{
    return d_func()->files == other.d_func()->files;
}

TCompiledProject::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCompiledProject &project)
{
    QVariantMap m;
    m.insert("files", project.d_func()->files);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompiledProject &project)
{
    QVariantMap m;
    stream >> m;
    project.d_func()->files = m.value("files").value<TProjectFileList>();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompiledProject &project)
{
    dbg.nospace() << "TCompiledProject(" << project.size() << ")";
    return dbg.space();
}
