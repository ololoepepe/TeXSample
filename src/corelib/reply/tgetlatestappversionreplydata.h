#ifndef TGETLATESTAPPVERSIONREPLYDATA_H
#define TGETLATESTAPPVERSIONREPLYDATA_H

class TGetLatestAppVersionReplyDataPrivate;

class BVersion;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLatestAppVersionReplyData ===============
============================================================================*/

class T_CORE_EXPORT TGetLatestAppVersionReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLatestAppVersionReplyData)
public:
    explicit TGetLatestAppVersionReplyData();
    TGetLatestAppVersionReplyData(const TGetLatestAppVersionReplyData &other);
    ~TGetLatestAppVersionReplyData();
public:
    void setVersion(const BVersion &version);
    BVersion version() const;
public:
    TGetLatestAppVersionReplyData &operator =(const TGetLatestAppVersionReplyData &other);
    bool operator ==(const TGetLatestAppVersionReplyData &other) const;
    bool operator !=(const TGetLatestAppVersionReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLatestAppVersionReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLatestAppVersionReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLatestAppVersionReplyData &data);
};

Q_DECLARE_METATYPE(TGetLatestAppVersionReplyData)

#endif // TGETLATESTAPPVERSIONREPLYDATA_H
