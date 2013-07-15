#ifndef TCOMPILERPARAMETERS_H
#define TCOMPILERPARAMETERS_H

class TCompilerParametersPrivate;

class QDataStream;
class QVariant;
class QDebug;
class QString;
class QTextCodec;
class QStringList;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>

/*============================================================================
================================ TCompilerParameters =========================
============================================================================*/

class TSMP_EXPORT TCompilerParameters : public BBase
{
    B_DECLARE_PRIVATE(TCompilerParameters)
    Q_DECLARE_TR_FUNCTIONS(TCompilerParameters)
public:
    enum Compiler
    {
        Tex,
        LaTex,
        PdfTex,
        PdfLaTex
    };
public:
    static QString compilerToString(Compiler c);
    static QString compilerToCommand(Compiler c);
    static Compiler compilerFromInt(int c);
public:
    explicit TCompilerParameters();
    TCompilerParameters(const TCompilerParameters &other);
    ~TCompilerParameters();
public:
    void setCodec(QTextCodec *codec);
    void setCodec(const QString &codecName);
    void setCompiler(int c);
    void setMakeindexEnabled(bool enabled);
    void setDvipsEnabled(bool enabled);
    void setOptions(const QStringList &list);
    void setOption(const QString &opt);
    void setCommands(const QStringList &list);
    void setCommand(const QString &cmd);
    QTextCodec *codec() const;
    QString codecName() const;
    Compiler compiler() const;
    QString compilerString() const;
    QString compilerCommand() const;
    bool makeindexEnabled() const;
    bool dvipsEnabled() const;
    QStringList options() const;
    QString optionsString(bool command = true) const;
    QStringList commands() const;
    QString commandsString(bool command = true) const;
public:
    TCompilerParameters &operator =(const TCompilerParameters &other);
    bool operator ==(const TCompilerParameters &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCompilerParameters &param);
    friend QDataStream &operator >>(QDataStream &stream, TCompilerParameters &param);
    friend QDebug operator <<(QDebug dbg, const TCompilerParameters &param);
};

Q_DECLARE_METATYPE(TCompilerParameters)

#endif // TCOMPILERPARAMETERS_H
