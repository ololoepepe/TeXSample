/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleCore module of the TeXSample library.
**
** TeXSample is free software: you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** TeXSample is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with TeXSample.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "taccesslevel.h"
#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BTranslator>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QVariantMap>

/*============================================================================
================================ TAccessLevelPrivate =========================
============================================================================*/

class TAccessLevelPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAccessLevel)
public:
   explicit TAccessLevelPrivate(TAccessLevel *q);
    ~TAccessLevelPrivate();
public:
    void init();
public:
    TAccessLevel::AccessLevel level;
private:
    Q_DISABLE_COPY(TAccessLevelPrivate)
};

/*============================================================================
================================ TAccessLevelPrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TAccessLevelPrivate::TAccessLevelPrivate(TAccessLevel *q) :
    BBasePrivate(q)
{
    //
}

TAccessLevelPrivate::~TAccessLevelPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAccessLevelPrivate::init()
{
    level = TAccessLevel::NoLevel;
}

/*============================================================================
================================ TAccessLevel ================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TAccessLevel::accessLevelToString(AccessLevel lvl, bool singular)
{
    switch (lvl) {
    case UserLevel:
        return singular ? tr("User", "singular") : tr("Users", "plural");
    case ModeratorLevel:
        return singular ? tr("Moderator", "singular") : tr("Moderators", "plural");
    case AdminLevel:
        return singular ? tr("Administrator", "singular") : tr("Administrators", "plural");
    case SuperuserLevel:
        return singular ? tr("Superuser", "singular") : tr("Superusers", "plural");
    case NoLevel:
    default:
        return singular ? tr("No", "singular") : tr("No", "plural");
    }
}

QString TAccessLevel::accessLevelToStringNoTr(AccessLevel lvl, bool singular)
{
    switch (lvl) {
    case UserLevel:
        return singular ? "User" : "Users";
    case ModeratorLevel:
        return singular ? "Moderator" : "Moderators";
    case AdminLevel:
        return singular ? "Administrator" : "Administrators";
    case SuperuserLevel:
        return singular ? "Superuser" : "Superusers";
    case NoLevel:
    default:
        return "No";
    }
}

QList<TAccessLevel> TAccessLevel::allAccessLevels(bool includeNoLevel)
{
    QList<TAccessLevel> list = QList<TAccessLevel>() << UserLevel << ModeratorLevel << AdminLevel << SuperuserLevel;
    if (includeNoLevel)
        list.prepend(NoLevel);
    return list;
}

/*============================== Public constructors =======================*/

TAccessLevel::TAccessLevel(int lvl) :
    BBase(*new TAccessLevelPrivate(this))
{
    d_func()->init();
    *this = lvl;
}

TAccessLevel::TAccessLevel(const TAccessLevel &other) :
    BBase(*new TAccessLevelPrivate(this))
{
    d_func()->init();
    *this = other;
}

TAccessLevel::~TAccessLevel()
{
    //
}

/*============================== Public methods ============================*/

bool TAccessLevel::isValid() const
{
    return NoLevel != d_func()->level;
}

TAccessLevel::AccessLevel TAccessLevel::level() const
{
    return d_func()->level;
}

QString TAccessLevel::toString() const
{
    return accessLevelToString(d_func()->level);
}

QString TAccessLevel::toStringNoTr() const
{
    return accessLevelToStringNoTr(d_func()->level);
}

/*============================== Public operators ==========================*/

TAccessLevel &TAccessLevel::operator =(const TAccessLevel &other)
{
    d_func()->level = other.d_func()->level;
    return *this;
}

TAccessLevel &TAccessLevel::operator =(int lvl)
{
    static const QList<int> Levels = bRangeM(UserLevel, SuperuserLevel);
    d_func()->level = Levels.contains(lvl) ? static_cast<AccessLevel>(lvl) : NoLevel;
    return *this;
}

bool TAccessLevel::operator ==(const TAccessLevel &other) const
{
    return d_func()->level == other.d_func()->level;
}

bool TAccessLevel::operator !=(const TAccessLevel &other) const
{
    return !(*this == other);
}

bool TAccessLevel::operator <(const TAccessLevel &other) const
{
    return d_func()->level < other.d_func()->level;
}

bool TAccessLevel::operator <=(const TAccessLevel &other) const
{
    return d_func()->level <= other.d_func()->level;
}

bool TAccessLevel::operator >(const TAccessLevel &other) const
{
    return d_func()->level > other.d_func()->level;
}

bool TAccessLevel::operator >=(const TAccessLevel &other) const
{
    return d_func()->level >= other.d_func()->level;
}

TAccessLevel::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TAccessLevel::operator int() const
{
    return (int) d_func()->level;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TAccessLevel &lvl)
{
    QVariantMap m;
    m.insert("level", (int) lvl.d_func()->level);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAccessLevel &lvl)
{
    QVariantMap m;
    stream >> m;
    lvl = m.value("level").toInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TAccessLevel &lvl)
{
    dbg.nospace() << "TAccessLevel(" << lvl.toStringNoTr() << ")";
    return dbg.space();
}
