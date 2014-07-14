#include "tbinaryfile.h"

#include "tnamespace.h"

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
================================ TBinaryFilePrivate ==========================
============================================================================*/

class TBinaryFilePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TBinaryFile)
public:
    QByteArray data;
    QString description;
    QString fileName;
    QString subpath;
public:
   explicit TBinaryFilePrivate(TBinaryFile *q);
    ~TBinaryFilePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TBinaryFilePrivate)
};

/*============================================================================
================================ TFilePrivate ================================
============================================================================*/

/*============================== Public constructors =======================*/

TBinaryFilePrivate::TBinaryFilePrivate(TBinaryFile *q) :
    BBasePrivate(q)
{
    //
}

TBinaryFilePrivate::~TBinaryFilePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TBinaryFilePrivate::init()
{
    //
}

/*============================================================================
================================ TBinaryFile =================================
============================================================================*/

/*============================== Public constructors =======================*/

TBinaryFile::TBinaryFile(const QString &fileaName, const QString &subpath) :
    BBase(*new TBinaryFilePrivate(this))
{
    d_func()->init();
    load(fileaName, subpath);
}

TBinaryFile::TBinaryFile(const TBinaryFile &other) :
    BBase(*new TBinaryFilePrivate(this))
{
    d_func()->init();
    *this = other;
}

TBinaryFile::~TBinaryFile()
{
    //
}

/*============================== Public methods ============================*/

void TBinaryFile::clear()
{
    B_D(TBinaryFile);
    d->fileName.clear();
    d->subpath.clear();
    d->data.clear();
    d->description.clear();
}

QByteArray TBinaryFile::data() const
{
    return d_func()->data;
}

QString TBinaryFile::description() const
{
    return d_func()->description;
}

QString TBinaryFile::fileName() const
{
    return d_func()->fileName;
}

bool TBinaryFile::isValid() const
{
    return !d_func()->fileName.isEmpty();
}

bool TBinaryFile::load(const QString &fileName, const QString &subpath)
{
    bool ok = false;
    d_func()->data = BDirTools::readFile(fileName, -1, &ok);
    if (!ok) {
        clear();
        return false;
    }
    setFileName(fileName);
    d_func()->subpath = subpath;
    return ok;
}

bool TBinaryFile::mayBeExecutable() const
{
    return BDirTools::mayBeExecutable(d_func()->data);
}

QString TBinaryFile::relativeFileName() const
{
    if (!isValid())
        return "";
    return d_func()->subpath + (!d_func()->subpath.isEmpty() ? "/" : "") + d_func()->fileName;
}

bool TBinaryFile::save(const QString &dir) const
{
    const B_D(TBinaryFile);
    if (!isValid() || dir.isEmpty())
        return false;
    QString fn = dir + (!d->subpath.isEmpty() ? ("/" + d->subpath) : QString()) + "/" + d->fileName;
    if (!BDirTools::writeFile(fn, d->data))
        return false;
    if (!mayBeExecutable())
        return true;
    QFile f(fn);
    bool b = f.setPermissions(f.permissions() | QFile::ExeUser);
    if (!b)
        f.remove();
    return b;
}

void TBinaryFile::setData(const QByteArray &data)
{
    d_func()->data = data;
}

void TBinaryFile::setDescription(const QString &description)
{
    d_func()->description = Texsample::testFileDescription(description) ? description : QString();
}

void TBinaryFile::setFileName(const QString &fileName)
{
    d_func()->fileName = !fileName.isEmpty() ? QFileInfo(fileName).fileName() : QString();
}

void TBinaryFile::setRelativeFileName(const QString &relativeFileName)
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

void TBinaryFile::setSubpath(const QString &subpath)
{
    d_func()->subpath = subpath;
}

int TBinaryFile::size() const
{
    return d_func()->data.size();
}

QString TBinaryFile::subpath() const
{
    return d_func()->subpath;
}

/*============================== Public operators ==========================*/

TBinaryFile &TBinaryFile::operator =(const TBinaryFile &other)
{
    B_D(TBinaryFile);
    const TBinaryFilePrivate *dd = other.d_func();
    d->fileName = dd->fileName;
    d->subpath = dd->subpath;
    d->data = dd->data;
    d->description = dd->description;
    return *this;
}

bool TBinaryFile::operator ==(const TBinaryFile &other) const
{
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive) {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    const B_D(TBinaryFile);
    const TBinaryFilePrivate *dd = other.d_func();
    return !d->fileName.compare(dd->fileName, cs) && !d->subpath.compare(dd->subpath, cs) && d->data == d->data
            && d->description == dd->description;
}

TBinaryFile::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TBinaryFile &file)
{
    const TBinaryFilePrivate *d = file.d_func();
    QVariantMap m;
    m.insert("file_name", d->fileName);
    m.insert("subpath", d->subpath);
    m.insert("data", d->data);
    m.insert("description", d->description);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TBinaryFile &file)
{
    TBinaryFilePrivate *d = file.d_func();
    QVariantMap m;
    stream >> m;
    d->fileName = m.value("file_name").toString();
    d->subpath = m.value("subpath").toString();
    d->data = m.value("data").toByteArray();
    d->description = m.value("description").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TBinaryFile &file)
{
    const TBinaryFilePrivate *d = file.d_func();
    dbg.nospace() << "TFile(" << d->fileName << ")";
    return dbg.space();
}
