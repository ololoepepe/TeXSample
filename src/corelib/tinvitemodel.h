#ifndef TINVITEMODEL_H
#define TINVITEMODEL_H

class TInviteModelPrivate;

class TIdList;
class TInviteInfo;
class TInviteInfoList;

class QObject;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QAbstractListModel>
#include <QModelIndex>

/*============================================================================
================================ TInviteModel ================================
============================================================================*/

class T_CORE_EXPORT TInviteModel : public QAbstractListModel, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TInviteModel)
public:
    explicit TInviteModel(QObject *parent = 0);
    ~TInviteModel();
public:
    void addInvite(const TInviteInfo &invite);
    void addInvites(const TInviteInfoList &inviteList);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    const TInviteInfo* inviteInfo(quint64 id) const;
    const TInviteInfo* inviteInfoAt(int index) const;
    void removeInvite(quint64 id);
    void removeInvites(const TIdList &idList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
private:
    Q_DISABLE_COPY(TInviteModel)
};

#endif // TINVITEMODEL_H

