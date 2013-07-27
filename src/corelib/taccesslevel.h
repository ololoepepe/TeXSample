#ifndef TACCESSLEVEL_H
#define TACCESSLEVEL_H

class TAccessLevelPrivate;

class QDataStream;
class QVariant;
class QDebug;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>
#include <QCoreApplication>
#include <QList>

/*============================================================================
================================ TAccessLevel ================================
============================================================================*/

class T_CORE_EXPORT TAccessLevel : public BBase
{
    B_DECLARE_PRIVATE(TAccessLevel)
    Q_DECLARE_TR_FUNCTIONS(TAccessLevel)
public:
    enum AccessLevel
    {
        NoLevel = 0,
        UserLevel = 10,
        ModeratorLevel = 100,
        AdminLevel = 1000,
        SuperuserLevel = 10000
    };
public:
    static QString accessLevelToString(AccessLevel lvl, bool singular = true);
    static QString accessLevelToStringNoTr(AccessLevel lvl, bool singular = true);
    static QList<TAccessLevel> allAccessLevels(bool includeNoLevel = false);
public:
    TAccessLevel(int lvl = NoLevel);
    TAccessLevel(const TAccessLevel &other);
    ~TAccessLevel();
public:
    QString toString() const;
    QString toStringNoTr() const;
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
