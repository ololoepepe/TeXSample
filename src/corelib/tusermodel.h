#ifndef TUSERMODEL_H
#define TUSERMODEL_H

class TUserModelPrivate;

class TIdList;
class TUserInfo;
class TUserInfoList;

class QObject;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QAbstractListModel>
#include <QModelIndex>

/*============================================================================
================================ TUserModel ==================================
============================================================================*/

class T_CORE_EXPORT TUserModel : public QAbstractListModel, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TUserModel)
public:
    explicit TUserModel(QObject *parent = 0);
    ~TUserModel();
public:
    void addUser(const TUserInfo &user);
    void addUsers(const TUserInfoList &userList);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    const TUserInfo* userInfo(quint64 id) const;
    const TUserInfo* userInfoAt(int index) const;
    void removeUser(quint64 id);
    void removeUsers(const TIdList &idList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
private:
    Q_DISABLE_COPY(TUserModel)
};

#endif // TUSERMODEL_H

