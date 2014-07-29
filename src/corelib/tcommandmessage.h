#ifndef TCOMMANDMESSAGE_H
#define TCOMMANDMESSAGE_H

class TCommandMessagePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TCommandMessage =============================
============================================================================*/

class T_CORE_EXPORT TCommandMessage : public BBase
{
    B_DECLARE_PRIVATE(TCommandMessage)
    Q_DECLARE_TR_FUNCTIONS(TCommandMessage)
public:
    enum Message
    {
        NoMessage = 0
    };
public:
    TCommandMessage(int msg = NoMessage);
    TCommandMessage(const TCommandMessage &other);
    ~TCommandMessage();
protected:
    explicit TCommandMessage(TCommandMessagePrivate &d);
public:
    QString text() const;
    QString textNoTr() const;
public:
    TCommandMessage &operator =(const TCommandMessage &other);
    TCommandMessage &operator =(int msg);
    bool operator ==(const TCommandMessage &other) const;
    bool operator !=(const TCommandMessage &other) const;
    operator QVariant() const;
    operator QString() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TCommandMessage &msg);
    friend QDataStream &operator >>(QDataStream &stream, TCommandMessage &msg);
    friend QDebug operator <<(QDebug dbg, const TCommandMessage &msg);
};

Q_DECLARE_METATYPE(TCommandMessage)

#endif // TCOMMANDMESSAGE_H
