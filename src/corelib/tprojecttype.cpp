#include "tprojecttype.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TProjectTypePrivate =========================
============================================================================*/

class TProjectTypePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TProjectType)
public:
    TProjectType::ProjectType type;
public:
   explicit TProjectTypePrivate(TProjectType *q);
    ~TProjectTypePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TProjectTypePrivate)
};

/*============================================================================
================================ TProjectTypePrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TProjectTypePrivate::TProjectTypePrivate(TProjectType *q) :
    BBasePrivate(q)
{
    //
}

TProjectTypePrivate::~TProjectTypePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TProjectTypePrivate::init()
{
    type = TProjectType::NoType;
}

/*============================================================================
================================ TProjectType ================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TProjectType::ProjectTypeToString(ProjectType type, bool singular)
{
    return tr(ProjectTypeToStringNoTr(type, singular).toUtf8().constData());
}

QString TProjectType::ProjectTypeToStringNoTr(ProjectType type, bool singular)
{
    switch (type)
    {
    case DesktopType:
        return singular ? QT_TRANSLATE_NOOP("TProjectType singular", "Desktop application") :
                          QT_TRANSLATE_NOOP("TProjectType plural", "Desktop applications");
    case WebType:
        return singular ? QT_TRANSLATE_NOOP("TProjectType singular", "Web application") :
                          QT_TRANSLATE_NOOP("TProjectType plural", "Web applications");
    case UrlType:
        return singular ? QT_TRANSLATE_NOOP("TProjectType singular", "External URL") :
                          QT_TRANSLATE_NOOP("TProjectType plural", "External URLs");
    case NoType:
    default:
        return singular ? QT_TRANSLATE_NOOP("TProjectType singular", "No application") :
                          QT_TRANSLATE_NOOP("TProjectType plural", "No applications");
    }
}

/*============================== Public constructors =======================*/

TProjectType::TProjectType(int type) :
    BBase(*new TProjectTypePrivate(this))
{
    d_func()->init();
    *this = type;
}

TProjectType::TProjectType(const TProjectType &other) :
    BBase(*new TProjectTypePrivate(this))
{
    d_func()->init();
    *this = other;
}

TProjectType::~TProjectType()
{
    //
}

/*============================== Public methods ============================*/

bool TProjectType::isValid() const
{
    return NoType != d_func()->type;
}

QString TProjectType::toString() const
{
    return ProjectTypeToString(d_func()->type);
}

QString TProjectType::toStringNoTr() const
{
    return ProjectTypeToStringNoTr(d_func()->type);
}

/*============================== Public operators ==========================*/

TProjectType &TProjectType::operator =(const TProjectType &other)
{
    d_func()->type = other.d_func()->type;
    return *this;
}

TProjectType &TProjectType::operator =(int type)
{
    static const QList<ProjectType> Types = QList<ProjectType>() << NoType << DesktopType << WebType
                                                                         << UrlType;
    d_func()->type = enum_cast<ProjectType>(type, Types, NoType);
    return *this;
}

bool TProjectType::operator ==(const TProjectType &other) const
{
    return d_func()->type == other.d_func()->type;
}

bool TProjectType::operator !=(const TProjectType &other) const
{
    return !(*this == other);
}

TProjectType::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TProjectType::operator int() const
{
    return (int) d_func()->type;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TProjectType &type)
{
    QVariantMap m;
    m.insert("type", (int) type.d_func()->type);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TProjectType &type)
{
    QVariantMap m;
    stream >> m;
    type = m.value("type").toInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TProjectType &type)
{
    dbg.nospace() << "TProjectType(" << type.toStringNoTr() << ")";
    return dbg.space();
}
