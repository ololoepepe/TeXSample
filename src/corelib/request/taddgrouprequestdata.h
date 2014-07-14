#ifndef TADDGROUPREQUESTDATA_H
#define TADDGROUPREQUESTDATA_H

class TAddGroupRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddGroupRequestData ========================
============================================================================*/

class T_CORE_EXPORT TAddGroupRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAddGroupRequestData)
public:
    explicit TAddGroupRequestData();
    TAddGroupRequestData(const TAddGroupRequestData &other);
    ~TAddGroupRequestData();
public:
    void clear();
    bool isValid() const;
    QString name() const;
    void setName(const QString &name);
public:
    TAddGroupRequestData &operator =(const TAddGroupRequestData &other);
    bool operator ==(const TAddGroupRequestData &other) const;
    bool operator !=(const TAddGroupRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddGroupRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddGroupRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAddGroupRequestData &data);
};

Q_DECLARE_METATYPE(TAddGroupRequestData)

#endif // TADDGROUPREQUESTDATA_H
