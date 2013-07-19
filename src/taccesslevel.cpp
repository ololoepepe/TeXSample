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
    switch (lvl)
    {
    case UserLevel:
        return singular ? tr("User") : tr("Users");
    case ModeratorLevel:
        return singular ? tr("Moderator") : tr("Moderators");
    case AdminLevel:
        return singular ? tr("Administrators") : tr("Administrators");
    case RootLevel:
        return singular ? tr("Root") : tr("Roots");
    case NoLevel:
    default:
        return singular ? tr("No", "accessLevel (singular)") : tr("No", "accessLevel (plural)");
    }
}

QString TAccessLevel::accessLevelToStringNoTr(AccessLevel lvl, bool singular)
{
    switch (lvl)
    {
    case UserLevel:
        return singular ? "User" : "Users";
    case ModeratorLevel:
        return singular ? "Moderator" : "Moderators";
    case AdminLevel:
        return singular ? "Administrator" : "Administrators";
    case RootLevel:
        return singular ? "Root" : "Roots";
    case NoLevel:
    default:
        return "No";
    }
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

    static const QList<int> Levels = bRangeM(UserLevel, RootLevel);
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
