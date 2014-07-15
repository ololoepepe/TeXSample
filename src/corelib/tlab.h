#ifndef TLAB_H
#define TLAB_H

class TLabPrivate;

class TProjectType;
class TProject;

class QDataStream;
class QDebug;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TLab ========================================
============================================================================*/

class T_CORE_EXPORT TLab : BBase
{
    B_DECLARE_PRIVATE(TLab)
public:
    explicit TLab();
    TLab(const TLab &other);
    ~TLab();
public:
    void clear();
    TProject &desktopApplication();
    const TProject &desktopApplication() const;
    bool isValid() const;
    void setDesktopApplication(const TProject &project);
    void setUrl(const QString &url);
    void setWebApplication(const TProject &project);
    int size() const;
    TProjectType type() const;
    QString url() const;
    TProject &webApplication();
    const TProject &webApplication() const;
public:
    TLab &operator =(const TLab &other);
    bool operator ==(const TLab &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TLab &lab);
    friend QDataStream &operator >>(QDataStream &stream, TLab &lab);
    friend QDebug operator <<(QDebug dbg, const TLab &lab);
};

Q_DECLARE_METATYPE(TLab)

#endif // TLAB_H
