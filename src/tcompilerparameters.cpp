#include "tcompilerparameters.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BeQt>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QTextCodec>
#include <QStringList>

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

QString TCompilerParameters::compilerToString(Compiler c, bool command)
{
    QString s;
    switch (c)
    {
    case Tex:
        s = "Tex";
        break;
    case LaTex:
        s = "LaTex";
        break;
    case PdfTex:
        s = "PdfTex";
        break;
    case PdfLaTex:
        s = "PdfLaTex";
        break;
    default:
        break;
    }
    return command ? s.toLower() : s;
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

void TCompilerParameters::setCompiler(Compiler c)
{
    d_func()->compiler = c;
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

void TCompilerParameters::setOption(const QString &opt)
{
    setOptions(QStringList() << opt);
}

void TCompilerParameters::setCommands(const QStringList &list)
{
    d_func()->commands = list;
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

QString TCompilerParameters::compilerString(bool command) const
{
    return compilerToString(d_func()->compiler, command);
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
    stream << d->codecName;
    stream << (int) d->compiler;
    stream << d->makeindex;
    stream << d->dvips;
    stream << d->options;
    stream << d->commands;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TCompilerParameters &param)
{
    static const QList<int> compilers = bRangeD(TCompilerParameters::Tex, TCompilerParameters::PdfLaTex);
    TCompilerParametersPrivate *d = param.d_func();
    stream >> d->codecName;
    int c = TCompilerParameters::PdfLaTex;
    stream >> c;
    d->compiler = compilers.contains(c) ? static_cast<TCompilerParameters::Compiler>(c) :
                                          TCompilerParameters::PdfLaTex;
    stream >> d->makeindex;
    stream >> d->dvips;
    stream >> d->options;
    stream >> d->commands;
    return stream;
}

QDebug operator <<(QDebug dbg, const TCompilerParameters &param)
{
    const TCompilerParametersPrivate *d = param.d_func();
    dbg.nospace() << "TCompilerParameters(" << d->codecName << "," << param.compilerString(false) << ","
                  << d->makeindex << "," << d->dvips << ")";
    return dbg.space();
}
