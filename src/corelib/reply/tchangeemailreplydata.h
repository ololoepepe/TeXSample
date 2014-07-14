#ifndef TCHANGEEMAILREPLYDATA_H
#define TCHANGEEMAILREPLYDATA_H

class TChangeEmailReplyDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TChangeEmailReplyData =======================
============================================================================*/

class TChangeEmailReplyData : public BBase
{
    B_DECLARE_PRIVATE(TChangeEmailReplyData)
public:
    explicit TChangeEmailReplyData();
    TChangeEmailReplyData(const TChangeEmailReplyData &other);
    ~TChangeEmailReplyData();
public:
    QString email() const;
    void setEmail(const QString &email);
public:
    TChangeEmailReplyData &operator =(const TChangeEmailReplyData &other);
    bool operator ==(const TChangeEmailReplyData &other) const;
    bool operator !=(const TChangeEmailReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TChangeEmailReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TChangeEmailReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TChangeEmailReplyData &data);
};

Q_DECLARE_METATYPE(TChangeEmailReplyData)

#endif // TCHANGEEMAILREPLYDATA_H
