#include "tlabtype.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TLabTypePrivate =============================
============================================================================*/

class TLabTypePrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TLabType)
public:
    TLabType::LabType type;
public:
   explicit TLabTypePrivate(TLabType *q);
    ~TLabTypePrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TLabTypePrivate)
};

/*============================================================================
================================ TLabTypePrivate =============================
============================================================================*/

/*============================== Public constructors =======================*/

TLabTypePrivate::TLabTypePrivate(TLabType *q) :
    BBasePrivate(q)
{
    //
}

TLabTypePrivate::~TLabTypePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TLabTypePrivate::init()
{
    type = TLabType::NoType;
}

/*============================================================================
================================ TLabType ====================================
============================================================================*/

/*============================== Static public methods =====================*/

QString TLabType::labTypeToString(LabType type, bool singular)
{
    return tr(labTypeToStringNoTr(type, singular).toUtf8().constData());
}

QString TLabType::labTypeToStringNoTr(LabType type, bool singular)
{
    switch (type) {
    case DesktopApplication:
        return singular ? QT_TRANSLATE_NOOP("TLabType singular", "Desktop application") :
                          QT_TRANSLATE_NOOP("TLabType plural", "Desktop applications");
    case WebApplication:
        return singular ? QT_TRANSLATE_NOOP("TLabType singular", "Web application") :
                          QT_TRANSLATE_NOOP("TLabType plural", "Web applications");
    case Url:
        return singular ? QT_TRANSLATE_NOOP("TLabType singular", "External URL") :
                          QT_TRANSLATE_NOOP("TLabType plural", "External URLs");
    case NoType:
    default:
        return singular ? QT_TRANSLATE_NOOP("TLabType singular", "No application") :
                          QT_TRANSLATE_NOOP("TLabType plural", "No applications");
    }
}

/*============================== Public constructors =======================*/

TLabType::TLabType(int type) :
    BBase(*new TLabTypePrivate(this))
{
    d_func()->init();
    *this = type;
}

TLabType::TLabType(const TLabType &other) :
    BBase(*new TLabTypePrivate(this))
{
    d_func()->init();
    *this = other;
}

TLabType::~TLabType()
{
    //
}

/*============================== Public methods ============================*/

bool TLabType::isValid() const
{
    return NoType != d_func()->type;
}

QString TLabType::toString() const
{
    return labTypeToString(d_func()->type);
}

QString TLabType::toStringNoTr() const
{
    return labTypeToStringNoTr(d_func()->type);
}

/*============================== Public operators ==========================*/

TLabType &TLabType::operator =(const TLabType &other)
{
    d_func()->type = other.d_func()->type;
    return *this;
}

TLabType &TLabType::operator =(int type)
{
    static const QList<LabType> Types = QList<LabType>() << NoType << DesktopApplication << WebApplication << Url;
    d_func()->type = enum_cast<LabType>(type, Types, NoType);
    return *this;
}

bool TLabType::operator ==(const TLabType &other) const
{
    return d_func()->type == other.d_func()->type;
}

bool TLabType::operator !=(const TLabType &other) const
{
    return !(*this == other);
}

TLabType::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

TLabType::operator int() const
{
    return (int) d_func()->type;
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TLabType &type)
{
    QVariantMap m;
    m.insert("type", (int) type.d_func()->type);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TLabType &type)
{
    QVariantMap m;
    stream >> m;
    type = m.value("type").toInt();
    return stream;
}

QDebug operator <<(QDebug dbg, const TLabType &type)
{
    dbg.nospace() << "TLabType(" << type.toStringNoTr() << ")";
    return dbg.space();
}
