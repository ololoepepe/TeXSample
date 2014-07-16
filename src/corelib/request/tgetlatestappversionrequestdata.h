#ifndef TGETLATESTAPPVERSIONREQUESTDATA_H
#define TGETLATESTAPPVERSIONREQUESTDATA_H

class TGetLatestAppVersionRequestDataPrivate;

class TClientInfo;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLatestAppVersionRequestData =============
============================================================================*/

class T_CORE_EXPORT TGetLatestAppVersionRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetLatestAppVersionRequestData)
public:
    explicit TGetLatestAppVersionRequestData();
    TGetLatestAppVersionRequestData(const TGetLatestAppVersionRequestData &other);
    ~TGetLatestAppVersionRequestData();
public:
    void clear();
    TClientInfo clientInfo() const;
    bool isValid() const;
    void setClientInfo(const TClientInfo &info);
public:
    TGetLatestAppVersionRequestData &operator =(const TGetLatestAppVersionRequestData &other);
    bool operator ==(const TGetLatestAppVersionRequestData &other) const;
    bool operator !=(const TGetLatestAppVersionRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLatestAppVersionRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLatestAppVersionRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLatestAppVersionRequestData &data);
};

Q_DECLARE_METATYPE(TGetLatestAppVersionRequestData)

#endif // TGETLATESTAPPVERSIONREQUESTDATA_H
