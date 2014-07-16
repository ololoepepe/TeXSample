#ifndef TGETLABDATAREPLYDATA_H
#define TGETLABDATAREPLYDATA_H

class TGetLabDataReplyDataPrivate;

class TLabData;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabDataReplyData ========================
============================================================================*/

class T_CORE_EXPORT TGetLabDataReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabDataReplyData)
public:
    explicit TGetLabDataReplyData();
    TGetLabDataReplyData(const TGetLabDataReplyData &other);
    ~TGetLabDataReplyData();
public:
    TLabData &data();
    const TLabData &data() const;
    void setData(const TLabData &data);
public:
    TGetLabDataReplyData &operator =(const TGetLabDataReplyData &other);
    bool operator ==(const TGetLabDataReplyData &other) const;
    bool operator !=(const TGetLabDataReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabDataReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabDataReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabDataReplyData &data);
};

Q_DECLARE_METATYPE(TGetLabDataReplyData)

#endif // TGETLABDATAREPLYDATA_H
