#ifndef TSAMPLEINFO_H
#define TSAMPLEINFO_H

class TSampleInfoPrivate;

class QDataStream;
class QString;

#include "tglobal.h"

#include <BeQtGlobal>
#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TSampleInfo =================================
============================================================================*/

class TSMP_EXPORT TSampleInfo : public BBase
{
    B_DECLARE_PRIVATE(TSampleInfo)
public:
    explicit TSampleInfo();
    TSampleInfo(const TSampleInfo &other);
    ~TSampleInfo();
protected:
    explicit TSampleInfo(TSampleInfoPrivate &d);
public:
    void setId(quint64 id);
    void setTitle(const QString &title);
    quint64 id() const;
    QString title() const;
public:
    TSampleInfo &operator=(const TSampleInfo &other);
public:
    friend QDataStream &operator<<(QDataStream &stream, const TSampleInfo &info);
    friend QDataStream &operator>>(QDataStream &stream, TSampleInfo &info);
};

Q_DECLARE_METATYPE(TSampleInfo)

#endif // TSAMPLEINFO_H
