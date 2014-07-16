#ifndef TREQUEST_H
#define TREQUEST_H

class TRequestPrivate;

class QDataStream;
class QDateTime;
class QDebug;
class QLocale;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TRequest ====================================
============================================================================*/

class T_CORE_EXPORT TRequest : public BBase
{
    B_DECLARE_PRIVATE(TRequest)
public:
    explicit TRequest();
    TRequest(const TRequest &other);
    ~TRequest();
public:
    bool cachingEnabled() const;
    void clear();
    QVariant data() const;
    QDateTime lastRequestDateTime() const;
    QLocale locale() const;
    void setCachingEnabled(bool enabled);
    void setData(const QVariant &data);
    void setLastRequestDateTime(const QDateTime &dt);
    void setLocale(const QLocale &locale);
public:
    TRequest &operator =(const TRequest &other);
    bool operator ==(const TRequest &other) const;
    bool operator !=(const TRequest &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TRequest &data);
    friend QDataStream &operator >>(QDataStream &stream, TRequest &data);
    friend QDebug operator <<(QDebug dbg, const TRequest &data);
};

Q_DECLARE_METATYPE(TRequest)

#endif // TREQUEST_H
