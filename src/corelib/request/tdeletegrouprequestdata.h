#ifndef TDELETEGROUPREQUESTDATA_H
#define TDELETEGROUPREQUESTDATA_H

class TDeleteGroupRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteGroupRequestData =====================
============================================================================*/

class T_CORE_EXPORT TDeleteGroupRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteGroupRequestData)
public:
    explicit TDeleteGroupRequestData();
    TDeleteGroupRequestData(const TDeleteGroupRequestData &other);
    ~TDeleteGroupRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TDeleteGroupRequestData &operator =(const TDeleteGroupRequestData &other);
    bool operator ==(const TDeleteGroupRequestData &other) const;
    bool operator !=(const TDeleteGroupRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteGroupRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteGroupRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteGroupRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteGroupRequestData)

#endif // TDELETEGROUPREQUESTDATA_H
