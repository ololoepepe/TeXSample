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
#include <QMap>

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
    return accessLevelToString(lvl, 0, singular);
}

QString TAccessLevel::accessLevelToString(AccessLevel lvl, BTranslator *translator, bool singular)
{
    struct TrStruct
    {
        const char *source;
        const char *comment;
    };
    static const TrStruct Singular[] =
    {
        QT_TRANSLATE_NOOP3("TAccessLevel", "No", "accessLevel (singular)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "User", "accessLevel (singular)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "Moderator", "accessLevel (singular)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "Administrator", "accessLevel (singular)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "Root", "accessLevel (singular)")
    };
    static const TrStruct Plural[] =
    {
        QT_TRANSLATE_NOOP3("TAccessLevel", "No", "accessLevel (plural)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "Users", "accessLevel (plural)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "Moderators", "accessLevel (plural)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "Administrators", "accessLevel (plural)"),
        QT_TRANSLATE_NOOP3("TAccessLevel", "Roots", "accessLevel (plural)")
    };
    const TrStruct *s = singular ? Singular : Plural;
    int ind = 0;
    switch (lvl)
    {
    case UserLevel:
        ind = 1;
        break;
    case ModeratorLevel:
        ind = 2;
        break;
    case AdminLevel:
        ind = 3;
        break;
    case RootLevel:
        ind = 4;
        break;
    case NoLevel:
    default:
        ind = 0;
        break;
    }
    return translator ? translator->translate("TAccessLevel", s[ind].source, s[ind].comment) :
                        tr(s[ind].source, s[ind].comment);
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

QString TAccessLevel::string(BTranslator *translator) const
{
    return accessLevelToString(d_func()->level, translator);
}

/*============================== Public operators ==========================*/

TAccessLevel &TAccessLevel::operator =(const TAccessLevel &other)
{
    d_func()->level = other.d_func()->level;
    return *this;
}

TAccessLevel &TAccessLevel::operator =(int lvl)
{
    static const QList<int> Levels = QList<int>() << NoLevel << UserLevel << ModeratorLevel << AdminLevel << RootLevel;
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
