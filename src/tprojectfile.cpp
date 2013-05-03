#include "tprojectfile.h"
#include "tglobal.h"
#include "ttexttools.h"

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
#include <QFileInfo>
#include <QByteArray>
#include <QTextCodec>
#include <QStringList>
#include <QRegExp>

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
    QString subdir;
    TProjectFile::Type type;
    QByteArray data;
    QString text;
private:
    Q_DISABLE_COPY(TProjectFilePrivate)
};

/*============================================================================
================================ TProjectFilePrivate =========================
============================================================================*/

/*============================== Static public methods =====================*/

QStringList TProjectFile::externalFiles(const QString &text, bool *ok)
{
    if (text.isEmpty())
        return bRet(ok, true, QStringList());
    init_once(Qt::CaseSensitivity, cs, Qt::CaseSensitive)
    {
#if defined(Q_OS_WIN)
        cs = Qt::CaseInsensitive;
#endif
    }
    static const QStringList schemes = QStringList() << "http" << "https" << "ftp";
    QRegExp what(".+");
    QRegExp pref("\\s*\\\\includegraphics(\\[.*\\])?\\{");
    QRegExp post("\\}");
    QStringList list = TTextTools::match(text, what, pref, post); // \includegraphics[...]{...}
    pref.setPattern("\\s*\\\\input\\s+");
    post.setPattern("");
    list << TTextTools::match(text, what, pref, post); // \input "..."
    pref.setPattern("\\\\href\\{(run\\:)?");
    post.setPattern("((\\\\)?\\#.+)?\\}\\{.+\\}");
    list << TTextTools::match(text, what, pref, post); // \href{run:...}{...}
    foreach (int i, bRangeR(list.size() - 1, 0))
    {
        list[i] = BeQt::unwrapped(list.at(i));
        if (QFileInfo(list.at(i)).isAbsolute())
            return bRet(ok, false, list);
        foreach (const QString &s, schemes)
        {
            if (list.at(i).left((s + "://").length()) == s + "://")
            {
                list.removeAt(i);
                break;
            }
        }
    }
    TTextTools::removeDuplicates(&list, cs);
    TTextTools::removeAll(&list, "texsample.tex", cs);
    TTextTools::sortComprising(&list, cs);
    return bRet(ok, true, list);
}

QStringList TProjectFile::externalFiles(const QString &fileName, QTextCodec *codec, bool *ok)
{
    bool bok = false;
    QString text = BDirTools::readTextFile(fileName, codec, &bok);
    if (!bok)
        return bRet(ok, false, QStringList());
    return externalFiles(text, ok);
}

QStringList TProjectFile::externalFiles(const QString &fileName, const QString &codecName, bool *ok)
{
    return externalFiles(fileName, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() :
                                                                                   QByteArray("UTF-8")), ok);
}

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

TProjectFile::TProjectFile(const QString &fileName, const QByteArray &data, const QString &subdir) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    setFileName(fileName);
    setSubdir(subdir);
    setData(data);
}

TProjectFile::TProjectFile(const QString &fileName, const QString &text, const QString &subdir) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    setFileName(fileName);
    setSubdir(subdir);
    setText(text);
}

TProjectFile::TProjectFile(const QString &fileName, Type type, QTextCodec *codec, const QString &subdir) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    if (Binary == type)
        loadAsBinary(fileName, subdir);
    else
        loadAsText(fileName, codec, subdir);
}

TProjectFile::TProjectFile(const QString &fileName, Type type, const QString &codecName, const QString &subdir) :
    BBase(*new TProjectFilePrivate(this))
{
    d_func()->init();
    if (Binary == type)
        loadAsBinary(fileName, subdir);
    else
        loadAsText(fileName, codecName, subdir);
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

void TProjectFile::setSubdir(const QString &subdir)
{
    d_func()->subdir = subdir;
}

void TProjectFile::setData(const QByteArray &data)
{
    d_func()->type = Binary;
    d_func()->text.clear();
    d_func()->data = data;
}

void TProjectFile::setText(const QString &text)
{
    d_func()->type = Text;
    d_func()->data.clear();
    d_func()->text = text;
}

void TProjectFile::clear()
{
    B_D(TProjectFile);
    d->fileName.clear();
    d->subdir.clear();
    d->type = Binary;
    d->data.clear();
    d->text.clear();
}

QString TProjectFile::fileName() const
{
    return d_func()->fileName;
}

QString TProjectFile::subdir() const
{
    return d_func()->subdir;
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

QStringList TProjectFile::externalFiles(bool *ok) const
{
    return externalFiles(d_func()->text, ok);
}

bool TProjectFile::wrapInputs()
{
    if (!isValid())
        return false;
    B_D(TProjectFile);
    if (d->text.isEmpty())
        return false;
    QString text = d->text;
    TTextTools::SearchResults list = TTextTools::match(text, QRegExp(".+"), QRegExp("\\s*\\\\input\\s+"));
    foreach (const TTextTools::SearchResult &r, list)
    {
        QString txt = r.text();
        if (txt.left(1) != "\"")
        {
            if (txt.right(1) != "\"")
                text.replace(r.position(), r.length(), txt.prepend("\"").append("\""));
            else
                return false;
        }
    }
    d->text = text;
    return true;
}

bool TProjectFile::removeTexsampleInput()
{
    if (!isValid())
        return false;
    B_D(TProjectFile);
    if (d->text.isEmpty())
        return false;
    QString text = d->text;
    TTextTools::SearchResults list = TTextTools::match(text, QRegExp("texsample\\.tex.*"), QRegExp("\\s*\\\\input\\s+"));
    foreach (const TTextTools::SearchResult &r, list)
        text.remove(r.position(), r.length());
    d->text = text;
    return true;
}

bool TProjectFile::loadAsBinary(const QString &fileName, const QString &subdir)
{
    bool ok = false;
    d_func()->type = Binary;
    d_func()->text.clear();
    d_func()->data = BDirTools::readFile(fileName, -1, &ok);
    setFileName(ok ? fileName : QString());
    setSubdir(subdir);
    return ok;
}

bool TProjectFile::loadAsText(const QString &fileName, QTextCodec *codec, const QString &subdir)
{
    bool ok = false;
    d_func()->type = Text;
    d_func()->data.clear();
    d_func()->text = BDirTools::readTextFile(fileName, codec, &ok);
    setFileName(ok ? fileName : QString());
    setSubdir(subdir);
    return ok;
}

bool TProjectFile::loadAsText(const QString &fileName, const QString &codecName, const QString &subdir)
{
    return loadAsText(fileName, QTextCodec::codecForName(!codecName.isEmpty() ? codecName.toLatin1() :
                                                                                QByteArray("UTF-8")), subdir);
}

bool TProjectFile::save(const QString &dir, QTextCodec *codec) const
{
    const B_D(TProjectFile);
    if (!isValid() || dir.isEmpty())
        return false;
    QString fn = dir + (!d->subdir.isEmpty() ? ("/" + d->subdir) : QString()) + "/" + d->fileName;
    return (Binary == d->type) ? BDirTools::writeFile(fn, d->data) : BDirTools::writeTextFile(fn, d->text, codec);
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
    d->subdir = dd->subdir;
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
    return !d->fileName.compare(dd->fileName, cs) && !d->subdir.compare(dd->subdir, cs) && d->type == dd->type
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
    stream << d->subdir;
    stream << (int) d->type;
    stream << d->data;
    stream << d->text;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TProjectFile &file)
{
    TProjectFilePrivate *d = file.d_func();
    stream >> d->fileName;
    stream >> d->subdir;
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
    dbg.nospace() << "TProjectFile(" << d->fileName << "," << d->subdir << "," << t << "," << file.size() << ")";
    return dbg.space();
}
