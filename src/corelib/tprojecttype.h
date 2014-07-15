#ifndef TPROJECTTYPE_H
#define TPROJECTTYPE_H

class TProjectTypePrivate;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QCoreApplication>
#include <QMetaType>

/*============================================================================
================================ TProjectType ================================
============================================================================*/

class T_CORE_EXPORT TProjectType : public BBase
{
    B_DECLARE_PRIVATE(TProjectType)
    Q_DECLARE_TR_FUNCTIONS(TProjectType)
public:
    enum ProjectType
    {
         NoType = 0,
         DesktopType,
         WebType,
         UrlType
    };
public:
    static QString ProjectTypeToString(ProjectType type, bool singular = true);
    static QString ProjectTypeToStringNoTr(ProjectType type, bool singular = true);
public:
    TProjectType(int type = NoType);
    TProjectType(const TProjectType &other);
    ~TProjectType();
public:
    bool isValid() const;
    QString toString() const;
    QString toStringNoTr() const;
public:
    TProjectType &operator =(const TProjectType &other);
    TProjectType &operator =(int type);
    bool operator ==(const TProjectType &other) const;
    bool operator !=(const TProjectType &other) const;
    operator QVariant() const;
    operator int() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TProjectType &type);
    friend QDataStream &operator >>(QDataStream &stream, TProjectType &type);
    friend QDebug operator <<(QDebug dbg, const TProjectType &type);
};

Q_DECLARE_METATYPE(TProjectType)

#endif // TPROJECTTYPE_H
