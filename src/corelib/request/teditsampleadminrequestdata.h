#ifndef TEDITSAMPLEADMINREQUESTDATA_H
#define TEDITSAMPLEADMINREQUESTDATA_H

class TEditSampleAdminRequestDataPrivate;

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
================================ TEditSampleAdminRequestData =================
============================================================================*/

class T_CORE_EXPORT TEditSampleAdminRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditSampleAdminRequestData)
public:
    explicit TEditSampleAdminRequestData();
    TEditSampleAdminRequestData(const TEditSampleAdminRequestData &other);
    ~TEditSampleAdminRequestData();
public:
    QString adminRemark() const;
    TAuthorInfoList authors() const;
    void clear();
    QString description() const;
    bool editProject() const;
    TIdList groups() const;
    bool isValid() const;
    TTexProject project() const;
    quint8 rating() const;
    void setAdminRemark(const QString &remark);
    void setAuthors(const TAuthorInfoList &authors);
    void setDescritpion(const QString &description);
    void setEditProject(bool edit);
    void setGroups(const TIdList &groups);
    void setProject(const TTexProject &project);
    void setRating(quint8 rating);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TEditSampleAdminRequestData &operator =(const TEditSampleAdminRequestData &other);
    bool operator ==(const TEditSampleAdminRequestData &other) const;
    bool operator !=(const TEditSampleAdminRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSampleAdminRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSampleAdminRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSampleAdminRequestData &data);
};

Q_DECLARE_METATYPE(TEditSampleAdminRequestData)

#endif // TEDITSAMPLEADMINREQUESTDATA_H
