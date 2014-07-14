#ifndef TFILEINFO_H
#define TFILEINFO_H

class TFileInfoPrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TFileInfo ===================================
============================================================================*/

class T_CORE_EXPORT TFileInfo : public BBase
{
    B_DECLARE_PRIVATE(TFileInfo)
public:
    explicit TFileInfo();
    TFileInfo(const TFileInfo &other);
    ~TFileInfo();
public:
    void clear();
    QString description() const;
    QString fileName() const;
    int fileSize() const;
    void setDescription(const QString &description);
    void setFileName(const QString &fileName);
    void setFileSize(int size);
public:
    TFileInfo &operator =(const TFileInfo &other);
    bool operator ==(const TFileInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TFileInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TFileInfo &info);
    friend QDebug operator <<(QDebug dbg, const TFileInfo &info);
};

Q_DECLARE_METATYPE(TFileInfo)

#endif // TFILEINFO_H
