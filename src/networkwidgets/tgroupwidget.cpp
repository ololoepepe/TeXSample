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

#include "tgroupwidget.h"
#include "tgroupwidget_p.h"

#include <TeXSampleCore/TAbstractCache>
#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TAddGroupReplyData>
#include <TeXSampleCore/TAddGroupRequestData>
#include <TeXSampleCore/TDeleteGroupRequestData>
#include <TeXSampleCore/TEditGroupReplyData>
#include <TeXSampleCore/TEditGroupRequestData>
#include <TeXSampleCore/TeXSample>
#include <TeXSampleCore/TGetGroupInfoListReplyData>
#include <TeXSampleCore/TGetGroupInfoListRequestData>
#include <TeXSampleCore/TGroupInfo>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TGroupModel>
#include <TeXSampleCore/TIdList>
#include <TeXSampleCore/TOperation>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TUserInfo>
#include <TeXSampleNetwork/TNetworkClient>

#include <BApplication>
#include <BDialog>
#include <BLineEdit>

#include <QAction>
#include <QApplication>
#include <QDateTime>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QModelIndex>
#include <QModelIndexList>
#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QSortFilterProxyModel>
#include <QString>
#include <QTableView>
#include <QToolBar>
#include <QVariant>
#include <QVBoxLayout>

/*============================================================================
================================ TGroupProxyModel ============================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupProxyModel::TGroupProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    //
}

/*============================== Public methods ============================*/

int TGroupProxyModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TGroupProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (Qt::DisplayRole != role && Qt::ToolTipRole != role) || index.column() > 1)
        return QVariant();
    TGroupModel *model = qobject_cast<TGroupModel *>(sourceModel());
    if (!model)
        return QVariant();
    TGroupInfo info = model->groupInfoAt(index.row());
    if (!info.isValid())
        return QVariant();
    if (Qt::ToolTipRole == role)
        return info.name() + " [" + info.ownerLogin() + "]"; //Name + OwnerLogin
    switch (index.column()) {
    case 0:
        return info.name(); //Name
    default:
        return QVariant();
    }
}

QVariant TGroupProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::Horizontal != orientation || Qt::DisplayRole != role)
        return QVariant();
    switch (section) {
    case 0:
        return sourceModel()->headerData(1, Qt::Horizontal); //Name
    default:
        return QVariant();
    }
}

/*============================================================================
================================ TGroupWidgetPrivate =========================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupWidgetPrivate::TGroupWidgetPrivate(TGroupWidget *q, TGroupModel *model) :
    BBaseObjectPrivate(q), Model(model)
{
    //
}

TGroupWidgetPrivate::~TGroupWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TGroupWidgetPrivate::init()
{
    cache = 0;
    client = 0;
    proxyModel = new TGroupProxyModel(this);
    proxyModel->setSourceModel(Model);
    B_Q(TGroupWidget);
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
        connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editGroup(QModelIndex)));
        connect(view->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                this, SLOT(selectionChanged(QItemSelection, QItemSelection)));
      vlt->addWidget(view);
      QToolBar *tbar = new QToolBar;
        actAdd = tbar->addAction(BApplication::icon("edit_add"), tr("Add group...", "act text"),
                                 this, SLOT(addGroup()));
          actAdd->setEnabled(false);
        actDelete = tbar->addAction(BApplication::icon("editdelete"), tr("Delete group", "act text"),
                                    this, SLOT(deleteGroup()));
          actDelete->setEnabled(false);
        actEdit = tbar->addAction(BApplication::icon("edit"), tr("Edit group...", "act text"),
                                  this, SLOT(editGroup()));
          actEdit->setEnabled(false);
      vlt->addWidget(tbar);
}

void TGroupWidgetPrivate::updateGroupList()
{
    if (!Model || !client || client->userInfo().accessLevel() < TAccessLevel(TAccessLevel::ModeratorLevel))
        return;
    TGetGroupInfoListRequestData request;
    TReply reply = client->performOperation(TOperation::GetGroupInfoList, request, Model->lastUpdateDateTime());
    if (!reply.success()) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Updating group list failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to update group list. The following error occured:", "msgbox text"));
        msg.setInformativeText(reply.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    TGetGroupInfoListReplyData data = reply.data().value<TGetGroupInfoListReplyData>();
    Model->update(data.newGroups(), data.deletedGroups(), reply.requestDateTime());
    if (cache && !reply.cacheUpToDate()) {
        cache->removeData(TOperation::GetGroupInfoList, data.deletedGroups());
        cache->setData(TOperation::GetGroupInfoList, reply.requestDateTime(), data);
    }
}

/*============================== Public slots ==============================*/

void TGroupWidgetPrivate::addGroup()
{
    if (!client || !client->isAuthorized())
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Adding group", "dlg windowTitle"));
      QWidget *wgt = new QWidget;
        QFormLayout *flt = new QFormLayout(wgt);
          BLineEdit *ledtName = new BLineEdit;
            ledtName->setValidator(new QRegExpValidator(QRegExp(".+"), ledtName));
            ledtName->checkValidity();
          flt->addRow(tr("Name:", "lbl text"), ledtName);
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()))->setEnabled(ledtName->hasAcceptableInput());
        connect(ledtName, SIGNAL(inputValidityChanged(bool)),
                dlg.button(QDialogButtonBox::Ok), SLOT(setEnabled(bool)));
      dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
    if (dlg.exec() != QDialog::Accepted)
        return;
    TAddGroupRequestData data;
    data.setName(ledtName->text());
    if (!data.isValid())
        return;
    TReply r = client->performOperation(TOperation::AddGroup, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Adding group failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to add group. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    TGroupInfo info = r.data().value<TAddGroupReplyData>().groupInfo();
    client->addAvailableGroup(info);
    Model->addGroup(info);
    if (cache)
        cache->setData(TOperation::AddGroup, r.requestDateTime(), r.data());
}

void TGroupWidgetPrivate::clientAuthorizedChanged(bool authorized)
{
    actAdd->setEnabled(client && authorized
                       && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::ModeratorLevel));
    selectionChanged(view->selectionModel()->selection(), QItemSelection());
    if (client && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel))
        updateGroupList();
}

void TGroupWidgetPrivate::deleteGroup()
{
    if (!client || !client->isAuthorized())
        return;
    QModelIndex index = proxyModel->mapToSource(view->selectionModel()->currentIndex());
    if (!index.isValid())
        return;
    TGroupInfo info = Model->groupInfoAt(index.row());
    if (!info.isValid())
        return;
    TDeleteGroupRequestData data;
    data.setId(info.id());
    TReply r = client->performOperation(TOperation::DeleteGroup, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Deleting group failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to delete group. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    client->removeAvailableGroup(info.id());
    Model->removeGroup(info.id());
    if (cache)
        cache->removeData(TOperation::DeleteGroup, info.id());
}

void TGroupWidgetPrivate::editGroup(QModelIndex index)
{
    if (!client || !client->isAuthorized())
        return;
    if (!index.isValid() && !view->selectionModel()->selectedIndexes().isEmpty())
        index = view->selectionModel()->selectedIndexes().first();
    if (!index.isValid())
        return;
    TGroupInfo info = Model->groupInfoAt(proxyModel->mapToSource(index).row());
    if (!info.isValid())
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Editing group", "dlg windowTitle"));
      QWidget *wgt = new QWidget;
        QFormLayout *flt = new QFormLayout(wgt);
          BLineEdit *ledtName = new BLineEdit;
            ledtName->setValidator(new QRegExpValidator(QRegExp(".+"), ledtName));
            ledtName->setText(info.name());
          flt->addRow(tr("Name:", "lbl text"), ledtName);
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()))->setEnabled(ledtName->hasAcceptableInput());
        connect(ledtName, SIGNAL(inputValidityChanged(bool)),
                dlg.button(QDialogButtonBox::Ok), SLOT(setEnabled(bool)));
      dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
    if (dlg.exec() != QDialog::Accepted)
        return;
    TEditGroupRequestData data;
    data.setId(info.id());
    data.setName(ledtName->text());
    if (!data.isValid())
        return;
    TReply r = client->performOperation(TOperation::EditGroup, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Editing group failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to edit group. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->updateGroup(info.id(), r.data().value<TEditGroupReplyData>().groupInfo());
    if (cache)
        cache->setData(TOperation::EditGroup, r.requestDateTime(), r.data(), info.id());
}

void TGroupWidgetPrivate::selectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    bool b = !selected.isEmpty() && !selected.first().indexes().isEmpty();
    QModelIndex ind = b ? proxyModel->mapToSource(selected.first().indexes().first()) : QModelIndex();
    b = b && ind.isValid();
    b = b && client && client->isAuthorized();
    b = b && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::ModeratorLevel);
    TGroupInfo info = Model->groupInfoAt(ind.row());
    b = b && info.isValid();
    b = b && (client->userInfo().availableGroups().contains(info)
              || client->userInfo().accessLevel().level() >= TAccessLevel::SuperuserLevel);
    actEdit->setEnabled(b);
    actDelete->setEnabled(b);
}

/*============================================================================
================================ TGroupWidget ================================
============================================================================*/

/*============================== Public constructors =======================*/

TGroupWidget::TGroupWidget(TGroupModel *model, QWidget *parent) :
    QWidget(parent), BBaseObject(*new TGroupWidgetPrivate(this, model))
{
    d_func()->init();
}

TGroupWidget::~TGroupWidget()
{
    //
}

/*============================== Public methods ============================*/

TAbstractCache *TGroupWidget::cache() const
{
    return d_func()->cache;
}

TNetworkClient *TGroupWidget::client() const
{
    return d_func()->client;
}

void TGroupWidget::setCache(TAbstractCache *cache)
{
    d_func()->cache = cache;
}

void TGroupWidget::setClient(TNetworkClient *client)
{
    B_D(TGroupWidget);
    if (d->client)
        disconnect(d->client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAuthorizedChanged(bool)));
    d->client = client;
    if (client)
        connect(client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAuthorizedChanged(bool)));
    d->actAdd->setEnabled(client && client->isAuthorized()
                          && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::ModeratorLevel));
    d->selectionChanged(d->view->selectionModel()->selection(), QItemSelection());
    if (client && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::ModeratorLevel))
        d->updateGroupList();
}
