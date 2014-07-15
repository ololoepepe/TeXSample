#ifndef TLABDATAINFO_H
#define TLABDATAINFO_H

class TLabDataInfoPrivate;

class TLabType;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TLabDataInfo ================================
============================================================================*/

class T_CORE_EXPORT TLabDataInfo : public BBase
{
    B_DECLARE_PRIVATE(TLabDataInfo)
public:
    explicit TLabDataInfo();
    TLabDataInfo(const TLabDataInfo &other);
    ~TLabDataInfo();
public:
    void clear();
    bool isValid() const;
    BeQt::OSType os() const;
    void setOs(BeQt::OSType os);
    void setSize(int size);
    void setType(const TLabType &type);
    int size() const;
    TLabType type() const;
public:
    TLabDataInfo &operator =(const TLabDataInfo &other);
    bool operator ==(const TLabDataInfo &other) const;
    bool operator !=(const TLabDataInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabDataInfo &data);
    friend QDataStream &operator >>(QDataStream &stream, TLabDataInfo &data);
    friend QDebug operator <<(QDebug dbg, const TLabDataInfo &data);
};

Q_DECLARE_METATYPE(TLabDataInfo)

#endif // TLABDATAINFO_H
