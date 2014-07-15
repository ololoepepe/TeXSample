#ifndef TSAMPLETYPE_H
#define TSAMPLETYPE_H

class TSampleTypePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TSampleType =================================
============================================================================*/

class T_CORE_EXPORT TSampleType : public BBase
{
    B_DECLARE_PRIVATE(TSampleType)
    Q_DECLARE_TR_FUNCTIONS(TSampleType)
public:
    enum SampleType
    {
         Unverified = 0,
         Approved = 10,
         Rejected = 100
    };
public:
    static QString sampleTypeToString(SampleType type, bool singular = true);
    static QString sampleTypeToStringNoTr(SampleType type, bool singular = true);
public:
    TSampleType(int type = Unverified);
    TSampleType(const TSampleType &other);
    ~TSampleType();
public:
    QString toString() const;
    QString toStringNoTr() const;
public:
    TSampleType &operator =(const TSampleType &other);
    TSampleType &operator =(int type);
    bool operator ==(const TSampleType &other) const;
    bool operator !=(const TSampleType &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TSampleType &type);
    friend QDataStream &operator >>(QDataStream &stream, TSampleType &type);
    friend QDebug operator <<(QDebug dbg, const TSampleType &type);
};

Q_DECLARE_METATYPE(TSampleType)

#endif // TSAMPLETYPE_H
