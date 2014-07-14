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
    return tr(accessLevelToStringNoTr(lvl, singular).toUtf8().constData());
}

QString TAccessLevel::accessLevelToStringNoTr(AccessLevel lvl, bool singular)
{
    switch (lvl)
    {
    case UserLevel:
        return singular ? QT_TRANSLATE_NOOP("TAccessLevel", "User") : QT_TRANSLATE_NOOP("TAccessLevel", "Users");
    case ModeratorLevel:
        return singular ? QT_TRANSLATE_NOOP("TAccessLevel", "Moderator") :
                          QT_TRANSLATE_NOOP("TAccessLevel", "Moderators");
    case AdminLevel:
        return singular ? QT_TRANSLATE_NOOP("TAccessLevel", "Administrator") :
                          QT_TRANSLATE_NOOP("TAccessLevel", "Administrators");
    case SuperuserLevel:
        return singular ? QT_TRANSLATE_NOOP("TAccessLevel", "Superuser") :
                          QT_TRANSLATE_NOOP("TAccessLevel", "Superusers");
    case NoLevel:
    default:
        return QT_TRANSLATE_NOOP("TAccessLevel", "No");
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
