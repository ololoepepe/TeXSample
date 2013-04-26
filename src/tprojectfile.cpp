#include "tprojectfile.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BDirTools>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <QByteArray>
#include <QTextCodec>

/*============================================================================
================================ TProjectFilePrivate =========================
============================================================================*/

class TProjectFilePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TProjectFile)
public:
   explicit TProjectFilePrivate(TProjectFile *q);
    ~TProjectFilePrivate();
public:
    void init();
public:
    QString fileName;
    TProjectFile::Type type;
    QByteArray data;
    QString text;
private:
    Q_DISABLE_COPY(TProjectFilePrivate)
};

/*============================================================================
================================ TProjectFilePrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TProjectFilePrivate::TProjectFilePrivate(TProjectFile *q) :
    BBasePrivate(q)
{
    //
}

TProjectFilePrivate::~TProjectFilePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TProjectFilePrivate::init()
{
    type = TProjectFile::Binary;
}

/*============================================================================
================================ TProjectFile ================================
============================================================================*/

/*============================== Public constructors =======================*/

TProjectFile::TProjectFile() :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
}

TProjectFile::TProjectFile(const QString &fileName, const QByteArray &data) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    setFileName(fileName);
    setData(data);
}

TProjectFile::TProjectFile(const QString &fileName, const QString &text) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    setFileName(fileName);
    setText(text);
}

TProjectFile::TProjectFile(const QString &fileName, Type type, QTextCodec *codec) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    if (Binary == type)
        loadAsBinary(fileName);
    else
        loadAsText(fileName, codec);
}

TProjectFile::TProjectFile(const QString &fileName, Type type, const QString &codecName) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    if (Binary == type)
        loadAsBinary(fileName);
    else
        loadAsText(fileName, codecName);
}

TProjectFile::TProjectFile(const TProjectFile &other) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    *this = other;
}

TProjectFile::~TProjectFile()
{
    //
}

/*============================== Public methods ============================*/

void TProjectFile::setFileName(const QString &fileName)
{
    d_func()->fileName = !fileName.isEmpty() ? QFileInfo(fileName).fileName() : QString();
}

void TProjectFile::setData(const QByteArray &data)
{
    d_func()->text.clear();
    d_func()->data = data;
}

void TProjectFile::setText(const QString &text)
{
    d_func()->data.clear();
    d_func()->text = text;
}

void TProjectFile::clear()
{
    B_D(TProjectFile);
    d->fileName.clear();
    d->type = Binary;
    d->data.clear();
    d->text.clear();
}

QString TProjectFile::fileName() const
{
    return d_func()->fileName;
}

TProjectFile::Type TProjectFile::type() const
{
    return d_func()->type;
}

QByteArray TProjectFile::data() const
{
    return d_func()->data;
}

QString TProjectFile::text() const
{
    return d_func()->text;
}

bool TProjectFile::loadAsBinary(const QString &fileName)
{
    bool ok = false;
    d_func()->type = Binary;
    d_func()->text.clear();
    d_func()->data = BDirTools::readFile(fileName, -1, &ok);
    setFileName(ok ? fileName : QString());
    return ok;
}

bool TProjectFile::loadAsText(const QString &fileName, QTextCodec *codec)
{
    bool ok = false;
    d_func()->type = Text;
    d_func()->data.clear();
    d_func()->text = BDirTools::readTextFile(fileName, codec, &ok);
    setFileName(ok ? fileName : QString());
    return ok;
}

bool TProjectFile::loadAsText(const QString &fileName, const QString &codecName)
{
    return loadAsText(fileName, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() :
                                                                                QByteArray("UTF-8")));
}

bool TProjectFile::save(const QString &dir, QTextCodec *codec) const
{
    const B_D(TProjectFile);
    return isValid() && !dir.isEmpty() && BDirTools::writeTextFile(dir + "/" + d->fileName, d->text, codec);
}

bool TProjectFile::save(const QString &dir, const QString &codecName) const
{
    return save(dir, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() : QByteArray("UTF-8")));
}

bool TProjectFile::isValid() const
{
    return !d_func()->fileName.isEmpty();
}

int TProjectFile::size() const
{
    return (d_func()->type == Binary) ? d_func()->data.size() : (d_func()->text.length() * 2);
}

/*============================== Public operators ==========================*/

TProjectFile &TProjectFile::operator =(const TProjectFile &other)
{
    B_D(TProjectFile);
    const TProjectFilePrivate *dd = other.d_func();
    d->fileName = dd->fileName;
    d->type = dd->type;
    d->data = dd->data;
    d->text = dd->text;
    return *this;
}

bool TProjectFile::operator ==(const TProjectFile &other) const
{
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive)
    {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    const B_D(TProjectFile);
    const TProjectFilePrivate *dd = other.d_func();
    return !d->fileName.compare(dd->fileName, cs) && d->type == dd->type
            && d->data == d->data && !d->text.compare(dd->text);
}

TProjectFile::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TProjectFile &file)
{
    const TProjectFilePrivate *d = file.d_func();
    stream << d->fileName;
    stream << (int) d->type;
    stream << d->data;
    stream << d->text;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TProjectFile &file)
{
    TProjectFilePrivate *d = file.d_func();
    stream >> d->fileName;
    int t = TProjectFile::Binary;
    stream >> t;
    d->type = bRangeD(TProjectFile::Binary, TProjectFile::Text).contains(t) ? static_cast<TProjectFile::Type>(t) :
                                                                              TProjectFile::Binary;
    stream >> d->data;
    stream >> d->text;
    return stream;
}

QDebug operator <<(QDebug dbg, const TProjectFile &file)
{
    const TProjectFilePrivate *d = file.d_func();
    QString t = (TProjectFile::Binary == d->type) ? "Binary" : "Text";
    dbg.nospace() << "TProjectFile(" << d->fileName << "," << t << "," << file.size() << ")";
    return dbg.space();
}
