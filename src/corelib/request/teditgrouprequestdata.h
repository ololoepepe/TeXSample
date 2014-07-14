#ifndef TEDITGROUPREQUESTDATA_H
#define TEDITGROUPREQUESTDATA_H

class TEditGroupRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditGroupRequestData =======================
============================================================================*/

class T_CORE_EXPORT TEditGroupRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditGroupRequestData)
public:
    explicit TEditGroupRequestData();
    TEditGroupRequestData(const TEditGroupRequestData &other);
    ~TEditGroupRequestData();
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    QString name() const;
    void setId(quint64 id);
    void setName(const QString &name);
public:
    TEditGroupRequestData &operator =(const TEditGroupRequestData &other);
    bool operator ==(const TEditGroupRequestData &other) const;
    bool operator !=(const TEditGroupRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditGroupRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditGroupRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditGroupRequestData &data);
};

Q_DECLARE_METATYPE(TEditGroupRequestData)

#endif // TEDITGROUPREQUESTDATA_H
