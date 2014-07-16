#ifndef TEDITLABREQUESTDATA_H
#define TEDITLABREQUESTDATA_H

class TEditLabRequestDataPrivate;

class TAuthorInfoList;
class TBinaryFileList;
class TIdList;
class TLabDataList;

class QDataStream;
class QDebug;
class QString;
class QStringList;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditLabRequestData =========================
============================================================================*/

class T_CORE_EXPORT TEditLabRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditLabRequestData)
public:
    explicit TEditLabRequestData();
    TEditLabRequestData(const TEditLabRequestData &other);
    ~TEditLabRequestData();
public:
    TAuthorInfoList authors() const;
    void clear();
    TLabDataList dataList() const;
    QStringList deletedExtraFiles() const;
    QString description() const;
    bool editData() const;
    TIdList groups() const;
    quint64 id() const;
    bool isValid() const;
    TBinaryFileList newExtraFiles() const;
    void setAuthors(const TAuthorInfoList &authors);
    void setDataList(const TLabDataList &dataList);
    void setDeletedExtraFiles(const QStringList &extraFiles);
    void setDescritpion(const QString &description);
    void setEditData(bool edit);
    void setGroups(const TIdList &groups);
    void setNewExtraFiles(const TBinaryFileList &extraFiles);
    void setTags(const QStringList &tags);
    void setTitle(const QString &title);
    QStringList tags() const;
    QString title() const;
public:
    TEditLabRequestData &operator =(const TEditLabRequestData &other);
    bool operator ==(const TEditLabRequestData &other) const;
    bool operator !=(const TEditLabRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditLabRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditLabRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditLabRequestData &data);
};

Q_DECLARE_METATYPE(TEditLabRequestData)

#endif // TEDITLABREQUESTDATA_H
