#ifndef TADDSAMPLEREQUESTDATA_H
#define TADDSAMPLEREQUESTDATA_H

class TAddSampleRequestDataPrivate;

class TAuthorInfoList;
class TIdList;
class TTexProject;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TAddSampleRequestData =======================
============================================================================*/

class T_CORE_EXPORT TAddSampleRequestData : public BBase
{
    B_DECLARE_PRIVATE(TAddSampleRequestData)
public:
    explicit TAddSampleRequestData();
    TAddSampleRequestData(const TAddSampleRequestData &other);
    ~TAddSampleRequestData();
public:
    TAuthorInfoList authors() const;
    void clear();
    QString description() const;
    TIdList groups() const;
    bool isValid() const;
    TTexProject project() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setDescritpion(const QString &description);
    void setGroups(const TIdList &groups);
    void setProject(const TTexProject &project);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TAddSampleRequestData &operator =(const TAddSampleRequestData &other);
    bool operator ==(const TAddSampleRequestData &other) const;
    bool operator !=(const TAddSampleRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TAddSampleRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TAddSampleRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TAddSampleRequestData &data);
};

Q_DECLARE_METATYPE(TAddSampleRequestData)

#endif // TADDSAMPLEREQUESTDATA_H
