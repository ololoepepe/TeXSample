#ifndef TUSERIDENTIFIER_H
#define TUSERIDENTIFIER_H

class TUserIdentifierPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TUserIdentifier =============================
============================================================================*/

class T_CORE_EXPORT TUserIdentifier : public BBase
{
    B_DECLARE_PRIVATE(TUserIdentifier)
public:
    explicit TUserIdentifier();
    TUserIdentifier(quint64 id);
    TUserIdentifier(const QString &login);
    TUserIdentifier(const TUserIdentifier &other);
    ~TUserIdentifier();
public:
    enum Type
    {
        NoType = 0,
        IdType,
        LoginType
    };
public:
    void clear();
    quint64 id() const;
    bool isValid() const;
    QString login() const;
    void setId(quint64 id);
    void setLogin(const QString &login);
    Type type() const;
public:
    TUserIdentifier &operator =(const TUserIdentifier &other);
    bool operator ==(const TUserIdentifier &other) const;
    bool operator !=(const TUserIdentifier &other) const;
    operator QVariant() const;
    operator quint64() const;
    operator QString() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TUserIdentifier &identificator);
    friend QDataStream &operator >>(QDataStream &stream, TUserIdentifier &identificator);
    friend QDebug operator <<(QDebug dbg, const TUserIdentifier &identificator);
};

Q_DECLARE_METATYPE(TUserIdentifier)

#endif // TUSERIDENTIFIER_H

