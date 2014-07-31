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

#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TAddGroupReplyData>
#include <TeXSampleCore/TAddGroupRequestData>
#include <TeXSampleCore/TDeleteGroupRequestData>
#include <TeXSampleCore/TEditGroupReplyData>
#include <TeXSampleCore/TEditGroupRequestData>
#include <TeXSampleCore/TGroupInfo>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TGroupModel>
#include <TeXSampleCore/TOperation>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TUserInfo>
#include <TeXSampleNetwork/TNetworkClient>

#include <BApplication>
#include <BDialog>

#include <QAction>
#include <QApplication>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QModelIndex>
#include <QString>
#include <QTableView>
#include <QToolBar>
#include <QVBoxLayout>

/*if (Qt::ToolTipRole == role)
    return info->name() + " [" + info->ownerLogin() + "]";
switch (index.column()) {
case 0:
    return info->id();
case 1:
    return info->name();
default:
    return QVariant();
}*/

//if (!index.isValid() || (Qt::DisplayRole != role && Qt::ToolTipRole != role) || index.column() > 1)
//    return QVariant();

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
    client = 0;
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
        view->setModel(Model);
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

/*============================== Public slots ==============================*/

void TGroupWidgetPrivate::addGroup()
{
    if (!client || !client->isAuthorized())
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Adding group", "dlg windowTitle"));
      QWidget *wgt = new QWidget;
        QFormLayout *flt = new QFormLayout(wgt);
          QLineEdit *ledtName = new QLineEdit;
          flt->addRow(tr("Name:", "lbl text"), ledtName);
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()));
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
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->addGroup(r.data().value<TAddGroupReplyData>().groupInfo());
}

void TGroupWidgetPrivate::clientAuthorizedChanged(bool authorized)
{
    actAdd->setEnabled(client && authorized
                       && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::ModeratorLevel));
    selectionChanged(view->selectionModel()->selection(), QItemSelection());
}

void TGroupWidgetPrivate::deleteGroup()
{
    if (!client || !client->isAuthorized())
        return;
    QModelIndex index = view->selectionModel()->currentIndex();
    if (!index.isValid())
        return;
    const TGroupInfo *info = Model->groupInfoAt(index.row());
    if (!info)
        return;
    TDeleteGroupRequestData data;
    data.setId(info->id());
    TReply r = client->performOperation(TOperation::DeleteGroup, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Deleting group failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to delete group. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->removeGroup(info->id());
}

void TGroupWidgetPrivate::editGroup(const QModelIndex &index)
{
    if (!client || !client->isAuthorized())
        return;
    if (!index.isValid())
        return;
    const TGroupInfo *info = Model->groupInfoAt(index.row());
    if (!info)
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Editing group", "dlg windowTitle"));
      QWidget *wgt = new QWidget;
        QFormLayout *flt = new QFormLayout(wgt);
          QLineEdit *ledtName = new QLineEdit;
            ledtName->setText(info->name());
          flt->addRow(tr("Name:", "lbl text"), ledtName);
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()));
      dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
    if (dlg.exec() != QDialog::Accepted)
        return;
    TEditGroupRequestData data;
    data.setId(info->id());
    data.setName(ledtName->text());
    if (!data.isValid())
        return;
    TReply r = client->performOperation(TOperation::EditGroup, data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Editing group failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to edit group. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageText());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
    Model->updateGroup(info->id(), r.data().value<TEditGroupReplyData>().groupInfo());
}

void TGroupWidgetPrivate::selectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    bool b = !selected.isEmpty() && !selected.first().indexes().isEmpty();
    QModelIndex ind = selected.first().indexes().first();
    b = b && ind.isValid();
    b = b && client && client->isAuthorized();
    b = b && client->userInfo().accessLevel() >= TAccessLevel(TAccessLevel::ModeratorLevel);
    const TGroupInfo *info = Model->groupInfoAt(ind.row());
    b = b && info;
    b = b && client->userInfo().availableGroups().contains(*info);
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

TNetworkClient *TGroupWidget::client() const
{
    return d_func()->client;
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
}
