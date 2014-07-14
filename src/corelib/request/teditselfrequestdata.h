#ifndef TEDITSELFREQUESTDATA_H
#define TEDITSELFREQUESTDATA_H

class TEditSelfRequestDataPrivate;

class QDataStream;
class QDebug;
class QImage;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditSelfRequestData ========================
============================================================================*/

class T_CORE_EXPORT TEditSelfRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditSelfRequestData)
public:
    explicit TEditSelfRequestData();
    TEditSelfRequestData(const TEditSelfRequestData &other);
    ~TEditSelfRequestData();
public:
    QImage avatar() const;
    void clear();
    bool editAvatar() const;
    QString name() const;
    QString patronymic() const;
    void setAvatar(const QImage &avatar);
    void setEditAvatar(bool edit);
    void setName(const QString &name);
    void setPatronymic(const QString &patronymic);
    void setSurename(const QString &surename);
    QString surename() const;
public:
    TEditSelfRequestData &operator =(const TEditSelfRequestData &other);
    bool operator ==(const TEditSelfRequestData &other) const;
    bool operator !=(const TEditSelfRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSelfRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSelfRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSelfRequestData &data);
};

Q_DECLARE_METATYPE(TEditSelfRequestData)

#endif // TEDITSELFREQUESTDATA_H
