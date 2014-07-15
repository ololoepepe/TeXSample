#ifndef TLABDATA_H
#define TLABDATA_H

class TLabDataPrivate;

class TLabApplication;
class TLabType;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TLabData ====================================
============================================================================*/

class T_CORE_EXPORT TLabData : public BBase
{
    B_DECLARE_PRIVATE(TLabData)
public:
    explicit TLabData();
    TLabData(const TLabData &other);
    ~TLabData();
public:
    TLabApplication &application();
    const TLabApplication &application() const;
    void clear();
    bool isValid() const;
    BeQt::OSType os() const;
    void setApplication(const TLabApplication &application);
    void setUrl(const QString &url);
    int size() const;
    TLabType type() const;
    QString url() const;
public:
    TLabData &operator =(const TLabData &other);
    bool operator ==(const TLabData &other) const;
    bool operator !=(const TLabData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLabData &data);
    friend QDataStream &operator >>(QDataStream &stream, TLabData &data);
    friend QDebug operator <<(QDebug dbg, const TLabData &data);
};

Q_DECLARE_METATYPE(TLabData)

#endif // TLABDATA_H
