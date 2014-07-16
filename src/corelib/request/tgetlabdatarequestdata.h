#ifndef TGETLABDATAREQUESTDATA_H
#define TGETLABDATAREQUESTDATA_H

class TGetLabDataRequestDataPrivate;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TGetLabDataRequestData ======================
============================================================================*/

class T_CORE_EXPORT TGetLabDataRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabDataRequestData)
public:
    explicit TGetLabDataRequestData();
    TGetLabDataRequestData(const TGetLabDataRequestData &other);
    ~TGetLabDataRequestData();
public:
    void clear();
    bool isValid() const;
    quint64 labId() const;
    BeQt::OSType os() const;
    void setLabId(quint64 id);
    void setOs(const BeQt::OSType os);
public:
    TGetLabDataRequestData &operator =(const TGetLabDataRequestData &other);
    bool operator ==(const TGetLabDataRequestData &other) const;
    bool operator !=(const TGetLabDataRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabDataRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabDataRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabDataRequestData &data);
};

Q_DECLARE_METATYPE(TGetLabDataRequestData)

#endif // TGETLABDATAREQUESTDATA_H
