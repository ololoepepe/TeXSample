#ifndef TPROJECTINFO_H
#define TPROJECTINFO_H

class TProjectInfoPrivate;

class TProjectType;

class QDataStream;
class QDebug;
class QVariant;

#include "tglobal.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>

/*============================================================================
================================ TProjectInfo ================================
============================================================================*/

class T_CORE_EXPORT TProjectInfo : public BBase
{
    B_DECLARE_PRIVATE(TProjectInfo)
public:
    explicit TProjectInfo();
    TProjectInfo(const TProjectInfo &other);
    ~TProjectInfo();
public:
    void clear();
    bool isValid() const;
    BeQt::OSType os() const;
    void setOs(BeQt::OSType os);
    void setSize(int size);
    void setType(const TProjectType &type);
    int size() const;
    TProjectType type() const;
public:
    TProjectInfo &operator =(const TProjectInfo &other);
    bool operator ==(const TProjectInfo &other) const;
    bool operator !=(const TProjectInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TProjectInfo &data);
    friend QDataStream &operator >>(QDataStream &stream, TProjectInfo &data);
    friend QDebug operator <<(QDebug dbg, const TProjectInfo &data);
};

Q_DECLARE_METATYPE(TProjectInfo)

#endif // TPROJECTINFO_H
