#ifndef TLABTYPE_H
#define TLABTYPE_H

class TLabTypePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TLabType ====================================
============================================================================*/

class T_CORE_EXPORT TLabType : public BBase
{
    B_DECLARE_PRIVATE(TLabType)
    Q_DECLARE_TR_FUNCTIONS(TLabType)
public:
    enum LabType
    {
         NoType = 0,
         DesktopApplication,
         WebApplication,
         Url
    };
public:
    static QString labTypeToString(LabType type, bool singular = true);
    static QString labTypeToStringNoTr(LabType type, bool singular = true);
public:
    TLabType(int type = NoType);
    TLabType(const TLabType &other);
    ~TLabType();
public:
    bool isValid() const;
    QString toString() const;
    QString toStringNoTr() const;
public:
    TLabType &operator =(const TLabType &other);
    TLabType &operator =(int type);
    bool operator ==(const TLabType &other) const;
    bool operator !=(const TLabType &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabType &type);
    friend QDataStream &operator >>(QDataStream &stream, TLabType &type);
    friend QDebug operator <<(QDebug dbg, const TLabType &type);
};

Q_DECLARE_METATYPE(TLabType)

#endif // TLABTYPE_H
