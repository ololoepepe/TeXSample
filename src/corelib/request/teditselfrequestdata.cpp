#include "teditselfrequestdata.h"

#include "tnamespace.h"

#include <BBase>
#include <BeQtCore/private/bbase_p.h>

#include <QDataStream>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QVariant>
#include <QVariantMap>

/*============================================================================
================================ TEditSelfRequestDataPrivate =================
============================================================================*/

class TEditSelfRequestDataPrivate : public BBasePrivate
{
    B_DECLARE_PUBLIC(TEditSelfRequestData)
public:
    QImage avatar;
    bool editAvatar;
    QString name;
    QString patronymic;
    QString surename;
public:
    explicit TEditSelfRequestDataPrivate(TEditSelfRequestData *q);
    ~TEditSelfRequestDataPrivate();
public:
    void init();
private:
    Q_DISABLE_COPY(TEditSelfRequestDataPrivate)
};

/*============================================================================
================================ TEditSelfRequestDataPrivate =================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfRequestDataPrivate::TEditSelfRequestDataPrivate(TEditSelfRequestData *q) :
    BBasePrivate(q)
{
    //
}

TEditSelfRequestDataPrivate::~TEditSelfRequestDataPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TEditSelfRequestDataPrivate::init()
{
    editAvatar = false;
}

/*============================================================================
================================ TEditSelfRequestData ========================
============================================================================*/

/*============================== Public constructors =======================*/

TEditSelfRequestData::TEditSelfRequestData() :
    BBase(*new TEditSelfRequestDataPrivate(this))
{
    d_func()->init();
}

TEditSelfRequestData::TEditSelfRequestData(const TEditSelfRequestData &other) :
    BBase(*new TEditSelfRequestDataPrivate(this))
{
    d_func()->init();
    *this = other;
}

TEditSelfRequestData::~TEditSelfRequestData()
{
    //
}

/*============================== Public methods ============================*/

QImage TEditSelfRequestData::avatar() const
{
    return d_func()->avatar;
}

void TEditSelfRequestData::clear()
{
    B_D(TEditSelfRequestData);
    d->avatar = QImage();
    d->editAvatar = false;
    d->name.clear();
    d->patronymic.clear();
    d->surename.clear();
}

bool TEditSelfRequestData::editAvatar() const
{
    return d_func()->editAvatar;
}

QString TEditSelfRequestData::name() const
{
    return d_func()->name;
}

QString TEditSelfRequestData::patronymic() const
{
    return d_func()->patronymic;
}

void TEditSelfRequestData::setAvatar(const QImage &avatar)
{
    d_func()->avatar = Texsample::testAvatar(avatar) ? avatar : QImage();
}

void TEditSelfRequestData::setEditAvatar(bool edit)
{
    d_func()->editAvatar = edit;
}

void TEditSelfRequestData::setName(const QString &name)
{
    d_func()->name = Texsample::testName(name) ? name : QString();
}

void TEditSelfRequestData::setPatronymic(const QString &patronymic)
{
    d_func()->patronymic = Texsample::testName(patronymic) ? patronymic : QString();
}

void TEditSelfRequestData::setSurename(const QString &surename)
{
    d_func()->surename = Texsample::testName(surename) ? surename : QString();
}

QString TEditSelfRequestData::surename() const
{
    return d_func()->surename;
}

/*============================== Public operators ==========================*/

TEditSelfRequestData &TEditSelfRequestData::operator =(const TEditSelfRequestData &other)
{
    B_D(TEditSelfRequestData);
    const TEditSelfRequestDataPrivate *dd = other.d_func();
    d->avatar = dd->avatar;
    d->editAvatar = dd->editAvatar;
    d->name = dd->name;
    d->patronymic = dd->patronymic;
    d->surename = dd->surename;
    return *this;
}

bool TEditSelfRequestData::operator ==(const TEditSelfRequestData &other) const
{
    const B_D(TEditSelfRequestData);
    const TEditSelfRequestDataPrivate *dd = other.d_func();
    return d->avatar == dd->avatar && d->editAvatar == dd->editAvatar && d->name == dd->name
            && d->patronymic == dd->patronymic && d->surename == dd->surename;
}

bool TEditSelfRequestData::operator !=(const TEditSelfRequestData &other) const
{
    return !(*this == other);
}

TEditSelfRequestData::operator QVariant() const
{
    return QVariant::fromValue(*this);
}

/*============================== Public friend operators ===================*/

QDataStream &operator <<(QDataStream &stream, const TEditSelfRequestData &data)
{
    const TEditSelfRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    if (d->editAvatar)
        m.insert("avatar", d->avatar);
    m.insert("edit_avatar", d->editAvatar);
    m.insert("name", d->name);
    m.insert("patronymic", d->patronymic);
    m.insert("surename", d->surename);
    stream << m;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TEditSelfRequestData &data)
{
    TEditSelfRequestDataPrivate *d = data.d_func();
    QVariantMap m;
    stream >> m;
    d->avatar = m.value("avatar").value<QImage>();
    d->editAvatar = m.value("edit_avatar").toBool();
    d->name = m.value("name").toString();
    d->patronymic = m.value("patronymic").toString();
    d->surename = m.value("surename").toString();
    return stream;
}

QDebug operator <<(QDebug dbg, const TEditSelfRequestData &/*data*/)
{
    //const TEditSelfRequestDataPrivate *d = data.d_func();
    dbg.nospace() << "TEditSelfRequestData(" << ")";
    return dbg.space();
}
