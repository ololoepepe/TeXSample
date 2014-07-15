#ifndef TGETSELFINFOREQUESTDATA_H
#define TGETSELFINFOREQUESTDATA_H

class TGetSelfInfoRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetSelfInfoRequestData =====================
============================================================================*/

class T_CORE_EXPORT TGetSelfInfoRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetSelfInfoRequestData)
public:
    explicit TGetSelfInfoRequestData();
    TGetSelfInfoRequestData(const TGetSelfInfoRequestData &other);
    ~TGetSelfInfoRequestData();
public:
    void clear();
    bool includeAvatar() const;
    void setIncludeAvatar(bool include);
public:
    TGetSelfInfoRequestData &operator =(const TGetSelfInfoRequestData &other);
    bool operator ==(const TGetSelfInfoRequestData &other) const;
    bool operator !=(const TGetSelfInfoRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetSelfInfoRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetSelfInfoRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetSelfInfoRequestData &data);
};

Q_DECLARE_METATYPE(TGetSelfInfoRequestData)

#endif // TGETSELFINFOREQUESTDATA_H
