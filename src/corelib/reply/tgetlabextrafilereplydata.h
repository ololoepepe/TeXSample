#ifndef TGETLABEXTRAFILEREPLYDATA_H
#define TGETLABEXTRAFILEREPLYDATA_H

class TGetLabExtraFileReplyDataPrivate;

class TBinaryFile;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TGetLabExtraFileReplyData ===================
============================================================================*/

class T_CORE_EXPORT TGetLabExtraFileReplyData : public BBase
{
    B_DECLARE_PRIVATE(TGetLabExtraFileReplyData)
public:
    explicit TGetLabExtraFileReplyData();
    TGetLabExtraFileReplyData(const TGetLabExtraFileReplyData &other);
    ~TGetLabExtraFileReplyData();
public:
    TBinaryFile &file();
    const TBinaryFile &file() const;
    void setFile(const TBinaryFile &file);
public:
    TGetLabExtraFileReplyData &operator =(const TGetLabExtraFileReplyData &other);
    bool operator ==(const TGetLabExtraFileReplyData &other) const;
    bool operator !=(const TGetLabExtraFileReplyData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TGetLabExtraFileReplyData &data);
    friend QDataStream &operator >>(QDataStream &stream, TGetLabExtraFileReplyData &data);
    friend QDebug operator <<(QDebug dbg, const TGetLabExtraFileReplyData &data);
};

Q_DECLARE_METATYPE(TGetLabExtraFileReplyData)

#endif // TGETLABEXTRAFILEREPLYDATA_H
