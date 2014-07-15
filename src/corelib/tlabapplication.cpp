#include "tlabapplication.h"

#include "tbinaryfile.h"
#include "tbinaryfilelist.h"

#include <BBase>
#include <BDirTools>
#include <BeQt>
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
================================ TLabApplicationPrivate ======================
============================================================================*/

class TLabApplicationPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLabApplication)
public:
    TBinaryFileList files;
    TBinaryFile mainFile;
    BeQt::OSType os;
public:
    explicit TLabApplicationPrivate(TLabApplication *q);
    ~TLabApplicationPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLabApplicationPrivate)
};

/*============================================================================
================================ TLabApplicationPrivate ======================
============================================================================*/

/*============================== Public constructors =======================*/

TLabApplicationPrivate::TLabApplicationPrivate(TLabApplication *q) :
    BBasePrivate(q)
{
    //
}

TLabApplicationPrivate::~TLabApplicationPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLabApplicationPrivate::init()
{
    os = BeQt::UnknownOS;
}

/*============================================================================
================================ TLabApplication =============================
============================================================================*/

/*============================== Public constructors =======================*/

TLabApplication::TLabApplication() :
    BBase(*new TLabApplicationPrivate(this))
{
    d_func()->init();
}

TLabApplication::TLabApplication(const TLabApplication &other) :
    BBase(*new TLabApplicationPrivate(this))
{
    d_func()->init();
    *this = other;
}

TLabApplication::~TLabApplication()
{
    //
}

/*============================== Public methods ============================*/

void TLabApplication::clear()
{
    B_D(TLabApplication);
    d->files.clear();
    d->mainFile.clear();
    d->os = BeQt::UnknownOS;
}

bool TLabApplication::isValid() const
{
    const B_D(TLabApplication);
    if (!d->mainFile.isValid())
        return false;
    foreach (const TBinaryFile &f, d->files) {
        if (!f.isValid())
            return false;
    }
    return (!d->mainFile.mayBeExecutable() || BeQt::UnknownOS != d->os);
}

bool TLabApplication::load(const QString &dir, const QString &relativeMainFileName, QStringList relativeFileNames)
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
    B_D(TLabApplication);
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

bool TLabApplication::mayBeExecutable() const
{
    return d_func()->mainFile.mayBeExecutable();
}

BeQt::OSType TLabApplication::os() const
{
    return d_func()->os;
}

bool TLabApplication::save(const QString &dir) const
{
    if (!isValid() || dir.isEmpty() || !d_func()->mainFile.save(dir))
        return false;
    foreach (const TBinaryFile &f, d_func()->files) {
        if (!f.save(dir))
            return false;
    }
    return true;
}

void TLabApplication::setOsType(BeQt::OSType os)
{
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d_func()->os = enum_cast<BeQt::OSType>(os, Types, BeQt::UnknownOS);
}

int TLabApplication::size() const
{
    if (!isValid())
        return 0;
    int sz = d_func()->mainFile.size();
    foreach (const TBinaryFile &f, d_func()->files)
        sz += f.size();
    return sz;
}

/*============================== Public operators ==========================*/

TLabApplication &TLabApplication::operator =(const TLabApplication &other)
{
    B_D(TLabApplication);
    const TLabApplicationPrivate *dd = other.d_func();
    d->files = dd->files;
    d->mainFile = dd->mainFile;
    d->os = dd->os;
    return *this;
}

bool TLabApplication::operator ==(const TLabApplication &other) const
{
    const B_D(TLabApplication);
    const TLabApplicationPrivate *dd = other.d_func();
    return d->files == dd->files && d->mainFile == dd->mainFile && d->os == dd->os;
}

TLabApplication::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLabApplication &project)
{
    const TLabApplicationPrivate *d = project.d_func();
    QVariantMap m;
    m.insert("files", d->files);
    m.insert("main_file", d->mainFile);
    m.insert("os", int(d->os));
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLabApplication &project)
{
    TLabApplicationPrivate *d = project.d_func();
    QVariantMap m;
    stream >> m;
    d->files = m.value("files").value<TBinaryFileList>();
    d->mainFile = m.value("main_file").value<TBinaryFile>();
    static const QList<BeQt::OSType> Types = QList<BeQt::OSType>() << BeQt::UnknownOS << BeQt::UnixOS
                                                                   << BeQt::WindowsOS << BeQt::LinuxOS << BeQt::MacOS;
    d->os = enum_cast<BeQt::OSType>(m.value("os"), Types, BeQt::UnknownOS);
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabApplication &project)
{
    dbg.nospace() << "TLabApplication(" << project.size() << ")";
    return dbg.space();
}
