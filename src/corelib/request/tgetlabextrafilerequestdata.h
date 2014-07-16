#ifndef TGETLABEXTRAFILEREQUESTDATA_H
#define TGETLABEXTRAFILEREQUESTDATA_H

class TGetLabExtraFileRequestDataPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabExtraFileRequestData =================
============================================================================*/

class T_CORE_EXPORT TGetLabExtraFileRequestData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabExtraFileRequestData)
public:
    explicit TGetLabExtraFileRequestData();
    TGetLabExtraFileRequestData(const TGetLabExtraFileRequestData &other);
    ~TGetLabExtraFileRequestData();
public:
    void clear();
    QString fileName() const;
    bool isValid() const;
    quint64 labId() const;
    void setFileName(const QString &fileName);
    void setLabId(quint64 id);
public:
    TGetLabExtraFileRequestData &operator =(const TGetLabExtraFileRequestData &other);
    bool operator ==(const TGetLabExtraFileRequestData &other) const;
    bool operator !=(const TGetLabExtraFileRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabExtraFileRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabExtraFileRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabExtraFileRequestData &data);
};

Q_DECLARE_METATYPE(TGetLabExtraFileRequestData)

#endif // TGETLABEXTRAFILEREQUESTDATA_H
