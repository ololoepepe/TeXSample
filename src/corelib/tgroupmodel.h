#ifndef TGROUPMODEL_H
#define TGROUPMODEL_H

class TGroupModelPrivate;

class TIdList;
class TGroupInfo;
class TGroupInfoList;

class QObject;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QAbstractListModel>
#include <QModelIndex>

/*============================================================================
================================ TGroupModel =================================
============================================================================*/

class TGroupModel : public QAbstractListModel, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TGroupModel)
public:
    explicit TGroupModel(QObject *parent = 0);
    ~TGroupModel();
public:
    void addGroup(const TGroupInfo &group);
    void addGroups(const TGroupInfoList &groupList);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    const TGroupInfo* groupInfo(quint64 id) const;
    const TGroupInfo* groupInfoAt(int index) const;
    void removeGroup(quint64 id);
    void removeGroups(const TIdList &idList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
private:
    Q_DISABLE_COPY(TGroupModel)
};

#endif // TGROUPMODEL_H

