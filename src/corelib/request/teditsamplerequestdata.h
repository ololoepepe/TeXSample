#ifndef TEDITSAMPLEREQUESTDATA_H
#define TEDITSAMPLEREQUESTDATA_H

class TEditSampleRequestDataPrivate;

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
================================ TEditSampleRequestData ======================
============================================================================*/

class T_CORE_EXPORT TEditSampleRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditSampleRequestData)
public:
    explicit TEditSampleRequestData();
    TEditSampleRequestData(const TEditSampleRequestData &other);
    ~TEditSampleRequestData();
public:
    TAuthorInfoList authors() const;
    void clear();
    QString description() const;
    bool editProject() const;
    TIdList groups() const;
    bool isValid() const;
    TTexProject project() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setDescritpion(const QString &description);
    void setEditProject(bool edit);
    void setGroups(const TIdList &groups);
    void setProject(const TTexProject &project);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TEditSampleRequestData &operator =(const TEditSampleRequestData &other);
    bool operator ==(const TEditSampleRequestData &other) const;
    bool operator !=(const TEditSampleRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSampleRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSampleRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSampleRequestData &data);
};

Q_DECLARE_METATYPE(TEditSampleRequestData)

#endif // TEDITSAMPLEREQUESTDATA_H
