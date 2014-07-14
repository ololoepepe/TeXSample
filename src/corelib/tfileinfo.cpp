#include "tfileinfo.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TFileInfoPrivate ============================
============================================================================*/

class TFileInfoPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TFileInfo)
public:
    QString description;
    QString fileName;
    int fileSize;
public:
   explicit TFileInfoPrivate(TFileInfo *q);
    ~TFileInfoPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TFileInfoPrivate)
};

/*============================================================================
================================ TFileInfoPrivate ============================
============================================================================*/

/*============================== Public constructors =======================*/

TFileInfoPrivate::TFileInfoPrivate(TFileInfo *q) :
    BBasePrivate(q)
{
    //
}

TFileInfoPrivate::~TFileInfoPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TFileInfoPrivate::init()
{
    fileSize = 0;
}

/*============================================================================
================================ TFileInfo ===================================
============================================================================*/

/*============================== Public constructors =======================*/

TFileInfo::TFileInfo() :
    BBase(*new TFileInfoPrivate(this))
{
    d_func()->init();
}

TFileInfo::TFileInfo(const TFileInfo &other) :
    BBase(*new TFileInfoPrivate(this))
{
    d_func()->init();
    *this = other;
}

TFileInfo::~TFileInfo()
{
    //
}

/*============================== Public methods ============================*/

void TFileInfo::clear()
{
    B_D(TFileInfo);
    d->description.clear();
    d->fileName.clear();
    d->fileSize = 0;
}

QString TFileInfo::description() const
{
    return d_func()->description;
}

QString TFileInfo::fileName() const
{
    return d_func()->fileName;
}

int TFileInfo::fileSize() const
{
    return d_func()->fileSize;
}

void TFileInfo::setDescription(const QString &description)
{
    d_func()->description = Texsample::testFileDescription(description) ? description : QString();
}

void TFileInfo::setFileName(const QString &fileName)
{
    d_func()->fileName = fileName;
}

void TFileInfo::setFileSize(int size)
{
    d_func()->fileSize = (size > 0) ? size : 0;
}

/*============================== Public operators ==========================*/

TFileInfo &TFileInfo::operator =(const TFileInfo &other)
{
    B_D(TFileInfo);
    const TFileInfoPrivate *dd = other.d_func();
    d->description = dd->description;
    d->fileName = dd->fileName;
    d->fileSize = dd->fileSize;
    return *this;
}

bool TFileInfo::operator ==(const TFileInfo &other) const
{
    const B_D(TFileInfo);
    const TFileInfoPrivate *dd = other.d_func();
    return d->description == dd->description && d->fileName == dd->fileName && d->fileSize == dd->fileSize;
}

TFileInfo::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TFileInfo &info)
{
    const TFileInfoPrivate *d = info.d_func();
    QVariantMap m;
    m.insert("description", d->description);
    m.insert("file_name", d->fileName);
    m.insert("file_size", d->fileSize);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TFileInfo &info)
{
    TFileInfoPrivate *d = info.d_func();
    QVariantMap m;
    stream >> m;
    d->description = m.value("description").toString();
    d->fileName = m.value("file_name").toString();
    d->fileSize = m.value("file_size").toInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TFileInfo &/*info*/)
{
    //const TFileInfoPrivate *d = info.d_func();
    dbg.nospace() << "TFileInfo(" << ")";
    return dbg.space();
}
