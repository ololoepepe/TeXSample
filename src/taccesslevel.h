#ifndef TACCESSLEVEL_H
#define TACCESSLEVEL_H

class TAccessLevelPrivate;

class QDataStream;
class QDateTime;
class QVariant;
class QDebug;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>

/*============================================================================
================================ TAccessLevel ================================
============================================================================*/

class TSMP_EXPORT TAccessLevel : public BBase
{
    B_DECLARE_PRIVATE(TAccessLevel)
    Q_DECLARE_TR_FUNCTIONS(TAccessLevel)
public:
    enum AccessLevel
    {
        NoLevel = 0,
        UserLevel = 10,
        ModeratorLevel = 100,
        AdminLevel = 1000
    };
public:
    static QString accessLevelToString(AccessLevel lvl, bool singular = true);
public:
    explicit TAccessLevel();
    TAccessLevel(int lvl);
    TAccessLevel(const TAccessLevel &other);
    ~TAccessLevel();
public:
    QString string() const;
public:
    TAccessLevel &operator =(const TAccessLevel &other);
    TAccessLevel &operator =(int lvl);
    bool operator ==(const TAccessLevel &other) const;
    bool operator !=(const TAccessLevel &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAccessLevel &lvl);
    friend QDataStream &operator >>(QDataStream &stream, TAccessLevel &lvl);
    friend QDebug operator <<(QDebug dbg, const TAccessLevel &lvl);
};

Q_DECLARE_METATYPE(TAccessLevel)

#endif // TACCESSLEVEL_H
