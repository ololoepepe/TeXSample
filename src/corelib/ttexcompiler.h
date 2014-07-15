#ifndef TTEXCOMPILER_H
#define TTEXCOMPILER_H

class TTexCompilerPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QList>
#include <QMetaType>

/*============================================================================
================================ TTexCompiler ================================
============================================================================*/

class T_CORE_EXPORT TTexCompiler : public BBase
{
    B_DECLARE_PRIVATE(TTexCompiler)
    Q_DECLARE_TR_FUNCTIONS(TTexCompiler)
public:
    enum Compiler
    {
        Unknown = 0,
        Tex,
        Latex,
        Pdftex,
        Pdflatex
    };
public:
    TTexCompiler(int compiler = Unknown);
    TTexCompiler(const TTexCompiler &other);
    ~TTexCompiler();
public:
    static QList<TTexCompiler> allCompilers(bool includeUnknown = false);
    static QString compilerToString(Compiler compiler);
public:
    bool isValid() const;
    QString toString() const;
public:
    TTexCompiler &operator =(const TTexCompiler &other);
    TTexCompiler &operator =(int compiler);
    bool operator ==(const TTexCompiler &other) const;
    bool operator !=(const TTexCompiler &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TTexCompiler &data);
    friend QDataStream &operator >>(QDataStream &stream, TTexCompiler &data);
    friend QDebug operator <<(QDebug dbg, const TTexCompiler &data);
};

Q_DECLARE_METATYPE(TTexCompiler)

#endif // TTEXCOMPILER_H
