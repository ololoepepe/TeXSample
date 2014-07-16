#ifndef TDELETELABREQUESTDATA_H
#define TDELETELABREQUESTDATA_H

class TDeleteLabRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TDeleteLabRequestData =======================
============================================================================*/

class T_CORE_EXPORT TDeleteLabRequestData : public BBase
{
    B_DECLARE_PRIVATE(TDeleteLabRequestData)
public:
    explicit TDeleteLabRequestData();
    TDeleteLabRequestData(const TDeleteLabRequestData &other);
    ~TDeleteLabRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    void setId(quint64 id);
public:
    TDeleteLabRequestData &operator =(const TDeleteLabRequestData &other);
    bool operator ==(const TDeleteLabRequestData &other) const;
    bool operator !=(const TDeleteLabRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TDeleteLabRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TDeleteLabRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TDeleteLabRequestData &data);
};

Q_DECLARE_METATYPE(TDeleteLabRequestData)

#endif // TDELETELABREQUESTDATA_H
