#ifndef TLOGREQUESTDATA_H
#define TLOGREQUESTDATA_H

class TLogRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BLogger>

#include <QMetaType>

/*============================================================================
================================ TLogRequestData =============================
============================================================================*/

class T_CORE_EXPORT TLogRequestData : public BBase
{
    B_DECLARE_PRIVATE(TLogRequestData)
public:
    explicit TLogRequestData();
    TLogRequestData(const TLogRequestData &other);
    ~TLogRequestData();
public:
    void clear();
    bool isValid() const;
    BLogger::Level level() const;
    void setLevel(BLogger::Level level);
    void setText(const QString &text);
    QString text() const;
public:
    TLogRequestData &operator =(const TLogRequestData &other);
    bool operator ==(const TLogRequestData &other) const;
    bool operator !=(const TLogRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLogRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TLogRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TLogRequestData &data);
};

Q_DECLARE_METATYPE(TLogRequestData)

#endif // TLOGREQUESTDATA_H
