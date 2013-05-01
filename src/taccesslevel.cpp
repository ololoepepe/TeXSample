#include "taccesslevel.h"

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QDataStream>
#include <QVariant>
#include <QDebug>
#include <QString>

/*============================================================================
================================ TAccessLevelPrivate =========================
============================================================================*/

class TAccessLevelPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TAccessLevel)
public:
   static TAccessLevel::AccessLevel accessLevelFromInt(int lvl);
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
    if (singular)
    {
        switch (lvl)
        {
        case UserLevel:
            return tr("User", "accessLevel (singular)");
        case ModeratorLevel:
            return tr("Moderator", "accessLevel (singular)");
        case AdminLevel:
            return tr("Administrator", "accessLevel (singular)");
        case NoLevel:
        default:
            return tr("No", "accessLevel (singular)");
        }
    }
    else
    {
        switch (lvl)
        {
        case UserLevel:
            return tr("Users", "accessLevel (plural)");
        case ModeratorLevel:
            return tr("Moderators", "accessLevel (plural)");
        case AdminLevel:
            return tr("Administrators", "accessLevel (plural)");
        case NoLevel:
        default:
            return tr("No", "accessLevel (singular)");
        }
    }
}

/*============================== Public constructors =======================*/

TAccessLevel::TAccessLevel() :
    BBase(*new TAccessLevelPrivate(this))
{
    d_func()->init();
}

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

QString TAccessLevel::string() const
{
    return accessLevelToString(d_func()->level);
}

/*============================== Public operators ==========================*/

TAccessLevel &TAccessLevel::operator =(const TAccessLevel &other)
{
    d_func()->level = other.d_func()->level;
    return *this;
}

TAccessLevel &TAccessLevel::operator =(int lvl)
{
    static const QList<int> Levels = QList<int>() << NoLevel << UserLevel << ModeratorLevel << AdminLevel;
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
    stream << (int) lvl.d_func()->level;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TAccessLevel &lvl)
{
    int l = 0;
    stream >> l;
    lvl = l;
    return stream;
}

QDebug operator <<(QDebug dbg, const TAccessLevel &lvl)
{
    dbg.nospace() << "TAccessLevel(" << lvl.string() << ")";
    return dbg.space();
}
