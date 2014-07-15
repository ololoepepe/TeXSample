#ifndef TAUTHORINFO_H
#define TAUTHORINFO_H

class TAuthorInfoPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAuthorInfo =================================
============================================================================*/

class T_CORE_EXPORT TAuthorInfo : public BBase
{
    B_DECLARE_PRIVATE(TAuthorInfo)
public:
    explicit TAuthorInfo();
    TAuthorInfo(const TAuthorInfo &other);
    ~TAuthorInfo();
public:
    void clear();
    bool isValid() const;
    QString name() const;
    QString organization() const;
    QString patronymic() const;
    QString post() const;
    QString role() const;
    void setName(const QString &name);
    void setOrganization(const QString &organization);
    void setPatronymic(const QString &patronymic);
    void setPost(const QString &post);
    void setRole(const QString &role);
    void setSurename(const QString &surename);
    QString surename() const;
public:
    TAuthorInfo &operator =(const TAuthorInfo &other);
    bool operator ==(const TAuthorInfo &other) const;
    bool operator !=(const TAuthorInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAuthorInfo &data);
    friend QDataStream &operator >>(QDataStream &stream, TAuthorInfo &data);
    friend QDebug operator <<(QDebug dbg, const TAuthorInfo &data);
};

Q_DECLARE_METATYPE(TAuthorInfo)

#endif // TAUTHORINFO_H
