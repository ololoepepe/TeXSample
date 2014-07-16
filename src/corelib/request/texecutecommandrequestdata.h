#ifndef TEXECUTECOMMANDREQUESTDATA_H
#define TEXECUTECOMMANDREQUESTDATA_H

class TExecuteCommandRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TExecuteCommandRequestData =============================
============================================================================*/

class T_CORE_EXPORT TExecuteCommandRequestData : public BBase
{
    B_DECLARE_PRIVATE(TExecuteCommandRequestData)
public:
    explicit TExecuteCommandRequestData();
    TExecuteCommandRequestData(const TExecuteCommandRequestData &other);
    ~TExecuteCommandRequestData();
public:
    QStringList arguments() const;
    void clear();
    QString command() const;
    bool isValid() const;
    void setArguments(const QStringList &arguments);
    void setCommand(const QString &command);
public:
    TExecuteCommandRequestData &operator =(const TExecuteCommandRequestData &other);
    bool operator ==(const TExecuteCommandRequestData &other) const;
    bool operator !=(const TExecuteCommandRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TExecuteCommandRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TExecuteCommandRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TExecuteCommandRequestData &data);
};

Q_DECLARE_METATYPE(TExecuteCommandRequestData)

#endif // TEXECUTECOMMANDREQUESTDATA_H
