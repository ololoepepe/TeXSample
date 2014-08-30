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

#include "tinvitewidget.h"
#include "tinvitewidget_p.h"

#include <TeXSampleCore/TAbstractCache>
#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TDeleteInvitesReplyData>
#include <TeXSampleCore/TDeleteInvitesRequestData>
#include <TeXSampleCore/TGenerateInvitesReplyData>
#include <TeXSampleCore/TGenerateInvitesRequestData>
#include <TeXSampleCore/TGetInviteInfoListReplyData>
#include <TeXSampleCore/TGetInviteInfoListRequestData>
#include <TeXSampleCore/TGroupInfo>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TIdList>
#include <TeXSampleCore/TInviteInfo>
#include <TeXSampleCore/TInviteInfoList>
#include <TeXSampleCore/TInviteModel>
#include <TeXSampleCore/TOperation>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>
#include <TeXSampleCore/TUserInfo>
#include <TeXSampleNetwork/TNetworkClient>
#include <TeXSampleWidgets/TGroupListWidget>
#include <TeXSampleWidgets/TInviteInfoWidget>
#include <TeXSampleWidgets/TServiceWidget>

#include <BApplication>
#include <BDialog>
#include <BeQt>
#include <BUuid>

#include <QAction>
#include <QClipboard>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QMap>
#include <QMessageBox>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include <QString>
#include <QTableView>
#include <QToolBar>
#include <QToolTip>
#include <QVariant>
#include <QVBoxLayout>

#include <climits>

/*============================================================================
================================ TInviteProxyModel ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteProxyModel::TInviteProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    //
}

/*============================== Public methods ============================*/

int TInviteProxyModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TInviteProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (Qt::DisplayRole != role && Qt::ToolTipRole != role) || index.column() > 1)
        return QVariant();
    TInviteModel *model = qobject_cast<TInviteModel *>(sourceModel());
    if (!model)
        return QVariant();
    TInviteInfo info = model->inviteInfoAt(index.row());
    if (!info.isValid())
        return QVariant();
    if (Qt::ToolTipRole == role)
        return info.code().toString(true) + " [" + info.ownerLogin() + "]"; //Code + OwnerLogin
    switch (index.column()) {
    case 0:
        //Expiration date
        return info.expirationDateTime().toString("dd MMMM yyyy hh:mm");
    default:
        return QVariant();
    }
}

QVariant TInviteProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::Horizontal != orientation || Qt::DisplayRole != role)
        return QVariant();
    switch (section) {
    case 0:
        return sourceModel()->headerData(7, Qt::Horizontal); //Expiration date
    default:
        return QVariant();
    }
}

/*============================================================================
================================ TInviteWidgetPrivate ========================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteWidgetPrivate::TInviteWidgetPrivate(TInviteWidget *q, TInviteModel *model) :
    BBaseObjectPrivate(q), Model(model)
{
    //
}

TInviteWidgetPrivate::~TInviteWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TInviteWidgetPrivate::init()
{
    cache = 0;
    client = 0;
    maxInviteCount = 0;
    proxyModel = new TInviteProxyModel(this);
    proxyModel->setSourceModel(Model);
    //
    B_Q(TInviteWidget);
    QVBoxLayout *vlt = new QVBoxLayout(q);
      view = new QTableView;
        view->setAlternatingRowColors(true);
        view->setEditTriggers(QTableView::NoEditTriggers);
        view->setSelectionBehavior(QTableView::SelectRows);
        view->setSelectionMode(QTableView::ExtendedSelection);
        view->horizontalHeader()->setStretchLastSection(true);
        view->verticalHeader()->setVisible(false);
        view->setContextMenuPolicy(Qt::NoContextMenu);
        view->setModel(proxyModel);
        connect(view->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                this, SLOT(selectionChanged(QItemSelection, QItemSelection)));
      vlt->addWidget(view);
      QToolBar *tbar = new QToolBar;
        actGenerate = tbar->addAction(BApplication::icon("edit_add"), tr("Generate invites...", "act text"),
                                      this, SLOT(generateInvites()));
          actGenerate->setEnabled(false);
        actInfo = tbar->addAction(BApplication::icon("messagebox_info"), tr("Info...", "act text"),
                                  this, SLOT(showInfo()));
          actInfo->setEnabled(false);
        actCopy = tbar->addAction(BApplication::icon("editcopy"), tr("Copy selected invite codes to clipboard",
                                                                     "act text"), this, SLOT(copyInvites()));
          actCopy->setEnabled(false);
        actDelete = tbar->addAction(BApplication::icon("editdelete"), tr("Delete selected invites", "act text"),
                                    this, SLOT(deleteInvites()));
          actDelete->setEnabled(false);
      vlt->addWidget(tbar);
}

void TInviteWidgetPrivate::updateInviteList()
{
    if (!Model || !client || client->userInfo().accessLevel() < TAccessLevel(TAccessLevel::AdminLevel))
        return;
    TGetInviteInfoListRequestData request;
    TReply reply = client->performOperation(TOperation::GetInviteInfoList, request, Model->lastUpdateDateTime());
    if (!reply.success()) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Updating invite list failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to update invite list. The following error occured:", "msgbox text"));
        msg.setInformativeText(reply.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    TGetInviteInfoListReplyData data = reply.data().value<TGetInviteInfoListReplyData>();
    Model->update(data.newInvites(), data.deletedInvites(), reply.requestDateTime());
    if (cache && !reply.cacheUpToDate())
        cache->setData(TOperation::GetInviteInfoList, reply.requestDateTime(), data);
}

/*============================== Public slots ==============================*/

void TInviteWidgetPrivate::clientAthorizedChanged(bool authorized)
{
    actDelete->setEnabled(client && authorized && view->selectionModel()->hasSelection());
    actGenerate->setEnabled(client && authorized
                            && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel));
    if (client && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel))
        updateInviteList();
}

void TInviteWidgetPrivate::copyInvites()
{
    QItemSelectionModel *sel = view->selectionModel();
    QStringList list;
    foreach (const QModelIndex &index, sel->selectedRows()) {
        if (!index.isValid())
            continue;
        TInviteInfo info = Model->inviteInfoAt(proxyModel->mapToSource(index).row());
        if (!info.isValid())
            continue;
        list << info.code().toString(true);
    }
    if (list.isEmpty())
        return;
    BApplication::clipboard()->setText(list.join("\n"));
    BeQt::waitNonBlocking(100);
    QString s = (list.size() > 1) ? tr("Invites were copied to clipboard", "toolTip") :
                                    tr("Invite was copied to clipboard", "toolTip");
    QToolTip::showText(view->mapToGlobal(view->visualRect(sel->currentIndex()).topLeft()), s, view);
}

void TInviteWidgetPrivate::deleteInvites()
{
    if (!client || !client->isAuthorized())
        return;
    TIdList list;
    foreach (const QModelIndex &index, view->selectionModel()->selectedRows()) {
        if (!index.isValid())
            continue;
        TInviteInfo info = Model->inviteInfoAt(proxyModel->mapToSource(index).row());
        if (!info.isValid())
            continue;
        list << info.id();
    }
    if (list.isEmpty())
        return;
    TDeleteInvitesRequestData data;
    data.setIds(list);
    TReply r = client->performOperation(TOperation::DeleteInvites, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Deleting invites failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to delete invites. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    TIdList ids = r.data().value<TDeleteInvitesReplyData>().identifiers();
    Model->removeInvites(ids);
    if (cache)
        cache->removeData(TOperation::DeleteInvites, ids);
}

void TInviteWidgetPrivate::generateInvites()
{
    if (!client || !client->isAuthorized()
            || client->userInfo().accessLevel() < TAccessLevel(TAccessLevel::AdminLevel))
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Generating invites", "dlg windowTitle"));
    TInviteInfoWidget *iiwgt = new TInviteInfoWidget;
    QList<TAccessLevel> levels;
    foreach (const TAccessLevel &lvl, TAccessLevel::allAccessLevels()) {
        if (lvl > client->userInfo().accessLevel())
            break;
        levels << lvl;
    }
    iiwgt->setAvailableAccessLevels(levels);
    iiwgt->setMaxInviteCount(maxInviteCount);
    iiwgt->setAvailableServices(client->userInfo().availableServices());
    iiwgt->setAvailableGroups(client->userInfo().availableGroups());
    dlg.setWidget(iiwgt);
    dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()));
    dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
    if (dlg.exec() != QDialog::Accepted)
        return;
    TGenerateInvitesRequestData data;
    data.setAccessLevel(iiwgt->accessLevel());
    data.setCount(iiwgt->count());
    data.setExpirationDateTime(iiwgt->expirationDateTime());
    data.setGroups(iiwgt->groupIds());
    data.setServices(iiwgt->services());
    if (!data.isValid())
        return;
    TReply r = client->performOperation(TOperation::GenerateInvites, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Generating invites failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to generate invites. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.message());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->addInvites(r.data().value<TGenerateInvitesReplyData>().generatedInvites());
    if (cache)
        cache->setData(TOperation::GenerateInvites, r.requestDateTime(), r.data());
}

void TInviteWidgetPrivate::selectionChanged(const QItemSelection &, const QItemSelection &)
{
    bool b = !view->selectionModel()->selectedRows().isEmpty();
    actCopy->setEnabled(b);
    actDelete->setEnabled(b && client);
    actInfo->setEnabled(view->selectionModel()->selectedRows().size() == 1);
}

void TInviteWidgetPrivate::showInfo()
{
    QItemSelectionModel *sel = view->selectionModel();
    if (sel->selectedRows().size() != 1)
        return;
    QModelIndex index = sel->selectedRows().first();
    if (!index.isValid())
        return;
    TInviteInfo info = Model->inviteInfoAt(proxyModel->mapToSource(index).row());
    if (!info.isValid())
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Invite info", "dlg windowTitle"));
    TInviteInfoWidget *iiwgt = new TInviteInfoWidget;
    iiwgt->setReadOnly(true);
    iiwgt->setInfo(info);
    dlg.setWidget(iiwgt);
    dlg.addButton(QDialogButtonBox::Close, SLOT(close()));
    dlg.exec();
}

/*============================================================================
================================ TInviteWidget ===============================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteWidget::TInviteWidget(TInviteModel *model, QWidget *parent) :
    QWidget(parent), BBaseObject(*new TInviteWidgetPrivate(this, model))
{
    d_func()->init();
}

TInviteWidget::~TInviteWidget()
{
    //
}

/*============================== Public methods ============================*/

TAbstractCache *TInviteWidget::cache() const
{
    return d_func()->cache;
}

TNetworkClient *TInviteWidget::client() const
{
    return d_func()->client;
}

quint16 TInviteWidget::maximumInviteCount() const
{
    return d_func()->maxInviteCount;
}

void TInviteWidget::setCache(TAbstractCache *cache)
{
    d_func()->cache = cache;
}

void TInviteWidget::setClient(TNetworkClient *client)
{
    B_D(TInviteWidget);
    if (d->client)
        disconnect(d->client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAthorizedChanged(bool)));
    d->client = client;
    if (client)
        connect(client, SIGNAL(authorizedChanged(bool)), d, SLOT(clientAthorizedChanged(bool)));
    d->actDelete->setEnabled(client && client->isAuthorized() && d->view->selectionModel()->hasSelection());
    d->actGenerate->setEnabled(client && client->isAuthorized()
                               && d->client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel));
    if (client && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::AdminLevel))
        d->updateInviteList();
}

void TInviteWidget::setMaximumInviteCount(quint16 count)
{
    d_func()->maxInviteCount = count;
}
