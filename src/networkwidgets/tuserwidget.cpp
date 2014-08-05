/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleNetworkWidgets module
** of the TeXSample library.
**
** TeXSample is free software: you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** TeXSample is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with TeXSample.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "tuserwidget.h"
#include "tuserwidget_p.h"

#include "tuserinfowidget.h"

#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TAddUserReplyData>
#include <TeXSampleCore/TAddUserRequestData>
#include <TeXSampleCore/TDeleteUserRequestData>
#include <TeXSampleCore/TEditUserReplyData>
#include <TeXSampleCore/TEditUserRequestData>
#include <TeXSampleCore/TUserInfo>
#include <TeXSampleCore/TUserInfoList>
#include <TeXSampleCore/TUserModel>
#include <TeXSampleCore/TOperation>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TUserIdentifier>
#include <TeXSampleCore/TUserInfo>
#include <TeXSampleNetwork/TNetworkClient>

#include <BApplication>
#include <BDialog>

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QImage>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QModelIndex>
#include <QModelIndexList>
#include <QPixmap>
#include <QPushButton>
#include <QSize>
#include <QSortFilterProxyModel>
#include <QString>
#include <QTableView>
#include <QToolBar>
#include <QVariant>
#include <QVBoxLayout>

/*============================================================================
================================ TUserProxyModel =============================
============================================================================*/

/*============================== Public constructors =======================*/

TUserProxyModel::TUserProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    //
}

/*============================== Public methods ============================*/

int TUserProxyModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant TUserProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (Qt::DisplayRole != role && Qt::ToolTipRole != role && Qt::DecorationRole != role
                             && Qt::CheckStateRole != role) || index.column() > 2)
        return QVariant();
    switch (index.column()) {
    case 0: {
    switch (role) {
    case Qt::DecorationRole: {
        //Avatar
        QPixmap p = QPixmap::fromImage(sourceModel()->data(sourceModel()->index(index.row(), 12)).value<QImage>());
        return p.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    case Qt::CheckStateRole: {
        //Active
        return sourceModel()->data(sourceModel()->index(index.row(), 3)).toBool() ? Qt::Checked : Qt::Unchecked;
    }
    default: {
        return QVariant();
    }
    }
    }
    case 1: {
        if (Qt::DisplayRole != role)
            return QVariant();
        return sourceModel()->data(sourceModel()->index(index.row(), 1)); //Login
    }
    case 2: {
        //Name [+ Patronymic] + Surname
        if (Qt::DisplayRole != role)
            return QVariant();
        QString name = sourceModel()->data(sourceModel()->index(index.row(), 5)).toString();
        QString patronymic = sourceModel()->data(sourceModel()->index(index.row(), 6)).toString();
        QString surname = sourceModel()->data(sourceModel()->index(index.row(), 7)).toString();
        return name + (!patronymic.isEmpty() ? (" " + patronymic) : QString()) + " " + surname;
    }
    default: {
        return QVariant();
    }
    }
}

QVariant TUserProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::Horizontal != orientation || (Qt::DisplayRole != role))
        return QVariant();
    switch (section) {
    case 0:
        return sourceModel()->headerData(3, Qt::Horizontal); //Active
    case 1:
        return sourceModel()->headerData(1, Qt::Horizontal); //Login
    case 2:
        return sourceModel()->headerData(5, Qt::Horizontal); //Name
    default:
        return QVariant();
    }
}

/*============================================================================
================================ TUserWidgetPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TUserWidgetPrivate::TUserWidgetPrivate(TUserWidget *q, TUserModel *model) :
    BBaseObjectPrivate(q), Model(model)
{
    //
}

TUserWidgetPrivate::~TUserWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TUserWidgetPrivate::init()
{
    client = 0;
    proxyModel = new TUserProxyModel(this);
    proxyModel->setSourceModel(Model);
    B_Q(TUserWidget);
    QVBoxLayout *vlt = new QVBoxLayout(q);
      view = new QTableView;
        view->setAlternatingRowColors(true);
        view->setEditTriggers(QTableView::NoEditTriggers);
        view->setSelectionBehavior(QTableView::SelectRows);
        view->setSelectionMode(QTableView::SingleSelection);
        view->horizontalHeader()->setStretchLastSection(true);
        view->verticalHeader()->setVisible(false);
        view->setContextMenuPolicy(Qt::NoContextMenu);
        view->setModel(proxyModel);
        connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editUser(QModelIndex)));
        connect(view->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                this, SLOT(selectionChanged(QItemSelection, QItemSelection)));
      vlt->addWidget(view);
      QToolBar *tbar = new QToolBar;
        actAdd = tbar->addAction(BApplication::icon("edit_add"), tr("Add user...", "act text"), this, SLOT(addUser()));
          actAdd->setEnabled(false);
        actDelete = tbar->addAction(BApplication::icon("editdelete"), tr("Delete user", "act text"),
                                    this, SLOT(deleteUser()));
          actDelete->setEnabled(false);
        actEdit = tbar->addAction(BApplication::icon("edit"), tr("Edit user...", "act text"), this, SLOT(editUser()));
          actEdit->setEnabled(false);
      vlt->addWidget(tbar);
}

/*============================== Public slots ==============================*/

void TUserWidgetPrivate::addUser()
{
    if (!client || !client->isAuthorized()
            || client->userInfo().accessLevel() < TAccessLevel(TAccessLevel::AdminLevel))
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Adding user", "dlg windowTitle"));
      TUserInfoWidget *wgt = new TUserInfoWidget(TUserInfoWidget::AddMode);
        wgt->setModel(Model);
        wgt->setClient(client);
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()))->setEnabled(false);
        connect(wgt, SIGNAL(inputValidityChanged(bool)), dlg.button(QDialogButtonBox::Ok), SLOT(setEnabled(bool)));
      dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
      dlg.resize(1000, 500);
    if (dlg.exec() != QDialog::Accepted)
        return;
    TAddUserRequestData data = wgt->createRequestData().value<TAddUserRequestData>();
    if (!data.isValid())
        return;
    TReply r = client->performOperation(TOperation::AddUser, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Adding user failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to add user. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->addUser(r.data().value<TAddUserReplyData>().userInfo());
}

void TUserWidgetPrivate::clientAuthorizedChanged(bool authorized)
{
    actAdd->setEnabled(client && authorized
                       && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel));
    selectionChanged(view->selectionModel()->selection(), QItemSelection());
}

void TUserWidgetPrivate::deleteUser()
{
    if (!client || !client->isAuthorized()
            || client->userInfo().accessLevel() < TAccessLevel(TAccessLevel::AdminLevel))
        return;
    QModelIndex index = proxyModel->mapToSource(view->selectionModel()->currentIndex());
    if (!index.isValid())
        return;
    quint64 userId = Model->userIdAt(index.row());
    if (!userId)
        return;
    TDeleteUserRequestData data;
    data.setIdentifier(userId);
    TReply r = client->performOperation(TOperation::DeleteUser, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Deleting user failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to delete user. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->removeUser(userId);
}

void TUserWidgetPrivate::editUser(QModelIndex index)
{
    if (!client || !client->isAuthorized()
            || client->userInfo().accessLevel() < TAccessLevel(TAccessLevel::AdminLevel))
        return;
    if (!index.isValid() && !view->selectionModel()->selectedIndexes().isEmpty())
        index = view->selectionModel()->selectedIndexes().first();
    if (!index.isValid())
        return;
    quint64 userId = Model->userIdAt(index.row());
    if (!userId)
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Editing user", "dlg windowTitle"));
      TUserInfoWidget *wgt = new TUserInfoWidget(TUserInfoWidget::EditMode);
        wgt->setModel(Model);
        wgt->setClient(client);
        wgt->setUser(userId);
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()))->setEnabled(wgt->hasValidInput());
        connect(wgt, SIGNAL(inputValidityChanged(bool)), dlg.button(QDialogButtonBox::Ok), SLOT(setEnabled(bool)));
      dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
      dlg.resize(1000, 500);
    if (dlg.exec() != QDialog::Accepted)
        return;
    TEditUserRequestData data = wgt->createRequestData().value<TEditUserRequestData>();
    if (!data.isValid())
        return;
    TReply r = client->performOperation(TOperation::EditUser, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Editing user failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to edit user. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->updateUser(userId, r.data().value<TEditUserReplyData>().userInfo(), data.editAvatar());
}

void TUserWidgetPrivate::selectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    bool b = !selected.isEmpty() && !selected.first().indexes().isEmpty();
    QModelIndex ind = b ? proxyModel->mapToSource(selected.first().indexes().first()) : QModelIndex();
    b = b && ind.isValid();
    b = b && client && client->isAuthorized();
    b = b && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel);
    TUserInfo info = Model->userInfoAt(ind.row());
    b = b && info.isValid();
    actEdit->setEnabled(b);
    actDelete->setEnabled(b);
}

/*============================================================================
================================ TUserWidget =================================
============================================================================*/

/*============================== Public constructors =======================*/

TUserWidget::TUserWidget(TUserModel *model, QWidget *parent) :
    QWidget(parent), BBaseObject(*new TUserWidgetPrivate(this, model))
{
    d_func()->init();
}

TUserWidget::~TUserWidget()
{
    //
}

/*============================== Public methods ============================*/

TNetworkClient *TUserWidget::client() const
{
    return d_func()->client;
}

void TUserWidget::setClient(TNetworkClient *client)
{
    B_D(TUserWidget);
    if (d->client)
        disconnect(d->client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAuthorizedChanged(bool)));
    d->client = client;
    if (client)
        connect(client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAuthorizedChanged(bool)));
    d->actAdd->setEnabled(client && client->isAuthorized()
                          && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel));
    d->selectionChanged(d->view->selectionModel()->selection(), QItemSelection());
}
