#include "tcompilerparameters.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BeQt>
#include <BTerminalIOHandler>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QTextCodec>
#include <QStringList>
#include <QVariantMap>
#include <QList>
#include <QRegExp>

/*============================================================================
================================ TCompilerParametersPrivate ==================
============================================================================*/

class TCompilerParametersPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TCompilerParameters)
public:
   explicit TCompilerParametersPrivate(TCompilerParameters *q);
    ~TCompilerParametersPrivate();
public:
    void init();
public:
    QString codecName;
    TCompilerParameters::Compiler compiler;
    bool makeindex;
    bool dvips;
    QStringList options;
    QStringList commands;
private:
    Q_DISABLE_COPY(TCompilerParametersPrivate)
};

/*============================================================================
================================ TCompilerParametersPrivate ==================
============================================================================*/

/*============================== Public constructors =======================*/

TCompilerParametersPrivate::TCompilerParametersPrivate(TCompilerParameters *q) :
    BBasePrivate(q)
{
    //
}

TCompilerParametersPrivate::~TCompilerParametersPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TCompilerParametersPrivate::init()
{
    codecName = "UTF-8";
    compiler = TCompilerParameters::PdfLaTex;
    makeindex = false;
    dvips = false;
}

/*============================================================================
================================ TCompilerParameters =========================
============================================================================*/

/*============================== Static public methods =====================*/

QString TCompilerParameters::compilerToString(Compiler c)
{
    c = compilerFromInt(c);
    switch (c)
    {
    case Tex:
        return "TeX";
    case LaTex:
        return "LaTeX";
    case PdfTex:
        return "PdfTeX";
    case PdfLaTex:
        return "PdfLaTeX";
    default:
        return "";
    }
}

QString TCompilerParameters::compilerToCommand(Compiler c)
{
    return compilerToString(c).toLower();
}

TCompilerParameters::Compiler TCompilerParameters::compilerFromInt(int c)
{
    static const QList<int> compilers = bRangeD(Tex, PdfLaTex);
    return compilers.contains(c) ? static_cast<Compiler>(c) : PdfLaTex;
}

QList<TCompilerParameters::Compiler> TCompilerParameters::allCompilers()
{
    return QList<Compiler>() << Tex << LaTex << PdfTex << PdfLaTex;
}

/*============================== Public constructors =======================*/

TCompilerParameters::TCompilerParameters() :
    BBase(*new TCompilerParametersPrivate(this))
{
    d_func()->init();
}

TCompilerParameters::TCompilerParameters(const TCompilerParameters &other) :
    BBase(*new TCompilerParametersPrivate(this))
{
    d_func()->init();
    *this = other;
}

TCompilerParameters::~TCompilerParameters()
{
    //
}

/*============================== Public methods ============================*/

void TCompilerParameters::setCodec(QTextCodec *codec)
{
    setCodec(codec ? QString(codec->name()) : QString());
}

void TCompilerParameters::setCodec(const QString &codecName)
{
    d_func()->codecName = !codecName.isEmpty() ? codecName : QString("UTF-8");
}

void TCompilerParameters::setCompiler(int c)
{
    d_func()->compiler = compilerFromInt(c);
}

void TCompilerParameters::setMakeindexEnabled(bool enabled)
{
    d_func()->makeindex = enabled;
}

void TCompilerParameters::setDvipsEnabled(bool enabled)
{
    d_func()->dvips = enabled;
}

void TCompilerParameters::setOptions(const QStringList &list)
{
    d_func()->options = list;
}

void TCompilerParameters::setOptions(const QString &s, bool command)
{
    if (command)
        setOptions(BTerminalIOHandler::splitCommand(s).mid(1));
    else
        setOptions(s.split(QRegExp("\\,\\s*"), QString::SkipEmptyParts));
}

void TCompilerParameters::setOption(const QString &opt)
{
    setOptions(QStringList() << opt);
}

void TCompilerParameters::setCommands(const QStringList &list)
{
    d_func()->commands = list;
}

void TCompilerParameters::setCommands(const QString &s, bool command)
{
    if (command)
        setCommands(BTerminalIOHandler::splitCommand(s).mid(1));
    else
        setCommands(s.split(QRegExp("\\,\\s*"), QString::SkipEmptyParts));
}

void TCompilerParameters::setCommand(const QString &cmd)
{
    setCommands(QStringList() << cmd);
}

QTextCodec *TCompilerParameters::codec() const
{
    return QTextCodec::codecForName(d_func()->codecName.toLatin1());
}

QString TCompilerParameters::codecName() const
{
    return d_func()->codecName;
}

TCompilerParameters::Compiler TCompilerParameters::compiler() const
{
    return d_func()->compiler;
}

QString TCompilerParameters::compilerString() const
{
    return compilerToString(d_func()->compiler);
}

QString TCompilerParameters::compilerCommand() const
{
    return compilerToCommand(d_func()->compiler);
}

bool TCompilerParameters::makeindexEnabled() const
{
    return d_func()->makeindex;
}

bool TCompilerParameters::dvipsEnabled() const
{
    return d_func()->dvips;
}

QStringList TCompilerParameters::options() const
{
    return d_func()->options;
}

QString TCompilerParameters::optionsString(bool command) const
{
    return d_func()->options.join(command ? " " : ", ");
}

QStringList TCompilerParameters::commands() const
{
    return d_func()->commands;
}

QString TCompilerParameters::commandsString(bool command) const
{
    return d_func()->commands.join(command ? " " : ", ");
}

/*============================== Public operators ==========================*/

TCompilerParameters &TCompilerParameters::operator =(const TCompilerParameters &other)
{
    B_D(TCompilerParameters);
    const TCompilerParametersPrivate *dd = other.d_func();
    d->codecName = dd->codecName;
    d->compiler = dd->compiler;
    d->makeindex = dd->makeindex;
    d->dvips = dd->dvips;
    d->options = dd->options;
    d->commands = dd->commands;
    return *this;
}

bool TCompilerParameters::operator ==(const TCompilerParameters &other) const
{
    const B_D(TCompilerParameters);
    const TCompilerParametersPrivate *dd = other.d_func();
    return !d->codecName.compare(dd->codecName, Qt::CaseInsensitive) && d->compiler == dd->compiler
            && d->makeindex == dd->makeindex && d->dvips == dd->dvips
            && d->options == dd->options && d->commands == dd->commands;
}

TCompilerParameters::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TCompilerParameters &param)
{
    const TCompilerParametersPrivate *d = param.d_func();
    QVariantMap m;
    m.insert("codec_name", d->codecName);
    m.insert("compiler", (int) d->compiler);
    m.insert("makeindex", d->makeindex);
    m.insert("dvips", d->dvips);
    m.insert("options", d->options);
    m.insert("commands", d->commands);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompilerParameters &param)
{
    TCompilerParametersPrivate *d = param.d_func();
    QVariantMap m;
    stream >> m;
    d->codecName = m.value("codec_name").toString();
    d->compiler = TCompilerParameters::compilerFromInt(m.value("compiler").toInt());
    d->makeindex = m.value("makeindex").toBool();
    d->dvips = m.value("dvips").toBool();
    d->options = m.value("options").toStringList();
    d->commands = m.value("commands").toStringList();
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompilerParameters &param)
{
    const TCompilerParametersPrivate *d = param.d_func();
    dbg.nospace() << "TCompilerParameters(" << d->codecName << "," << param.compilerString() << ","
                  << d->makeindex << "," << d->dvips << ")";
    return dbg.space();
}
