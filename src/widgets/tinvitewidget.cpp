#include "tinvitewidget.h"
#include "tinvitewidget_p.h"

#include "tlistwidget.h"

#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TDeleteInvitesReplyData>
#include <TeXSampleCore/TDeleteInvitesRequestData>
#include <TeXSampleCore/TGenerateInvitesReplyData>
#include <TeXSampleCore/TGenerateInvitesRequestData>
#include <TeXSampleCore/TGroupInfo>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TIdList>
#include <TeXSampleCore/TInviteInfo>
#include <TeXSampleCore/TInviteModel>
#include <TeXSampleCore/TReply>
#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>

#include <BApplication>
#include <BDialog>
#include <BeQt>
#include <BUuid>

#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QClipboard>
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QMap>
#include <QMessageBox>
#include <QModelIndex>
#include <QSpinBox>
#include <QString>
#include <QTableView>
#include <QToolBar>
#include <QToolTip>
#include <QVariant>
#include <QVBoxLayout>

#include <climits>

/*============================================================================
================================ TInviteWidgetPrivate ========================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteWidgetPrivate::TInviteWidgetPrivate(TInviteWidget *q, TInviteModel *model, const TAccessLevel &accessLevel) :
    BBaseObjectPrivate(q), AccessLevel(accessLevel), Model(model)
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
        view->setModel(Model);
        connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(copyInvite(QModelIndex)));
        connect(view->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                this, SLOT(selectionChanged(QItemSelection, QItemSelection)));
      vlt->addWidget(view);
      QToolBar *tbar = new QToolBar;
        actGenerate = tbar->addAction(BApplication::icon("edit_add"), tr("Generate invites...", "act text"),
                                      this, SLOT(generateInvites()));
          actGenerate->setEnabled(false);
        actCopy = tbar->addAction(BApplication::icon("editcopy"), tr("Copy selected invite codes to clipboard",
                                                                     "act text"), this, SLOT(copyInvites()));
          actCopy->setEnabled(false);
        actDelete = tbar->addAction(BApplication::icon("editdelete"), tr("Delete selected invites", "act text"),
                                    this, SLOT(deleteInvites()));
          actDelete->setEnabled(false);
      vlt->addWidget(tbar);
}

/*============================== Public slots ==============================*/

void TInviteWidgetPrivate::copyInvites()
{
    QItemSelectionModel *sel = view->selectionModel();
    QStringList list;
    foreach (const QModelIndex &index, sel->selectedRows()) {
        if (!index.isValid())
            continue;
        const TInviteInfo *info = Model->inviteInfoAt(index.row());
        if (!info)
            continue;
        list << BeQt::pureUuidText(info->code());
    }
    if (list.isEmpty())
        return;
    QApplication::clipboard()->setText(list.join("\n"));
    BeQt::waitNonBlocking(100);
    QString s = (list.size() > 1) ? tr("Invite were copied to clipboard", "toolTip") :
                                    tr("Invite was copied to clipboard", "toolTip");
    QToolTip::showText(view->mapToGlobal(view->visualRect(sel->currentIndex()).topLeft()), s, view);
}

void TInviteWidgetPrivate::deleteInvites()
{
    if (!deleteInvitesFunction)
        return;
    TIdList list;
    foreach (const QModelIndex &index, view->selectionModel()->selectedRows()) {
        if (!index.isValid())
            continue;
        const TInviteInfo *info = Model->inviteInfoAt(index.row());
        if (!info)
            continue;
        list << info->id();
    }
    if (list.isEmpty())
        return;
    TDeleteInvitesRequestData data;
    data.setIds(list);
    TReply r = deleteInvitesFunction(data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Deleting invites failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to delete invites. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageString());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
}

void TInviteWidgetPrivate::generateInvites()
{
    if (!generateInvitesFunction || AccessLevel < TAccessLevel(TAccessLevel::ModeratorLevel))
        return;
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Generating invites", "dlg windowTitle"));
      QWidget *wgt = new QWidget;
        QVBoxLayout *vlt = new QVBoxLayout(wgt);
          QFormLayout *flt = new QFormLayout;
            QComboBox *cmboxAccessLevel = new QComboBox;
              foreach (const TAccessLevel &lvl, TAccessLevel::allAccessLevels()) {
                  if (lvl > AccessLevel)
                      break;
                  cmboxAccessLevel->addItem(lvl.toString(), int(lvl));
              }
              if (cmboxAccessLevel->count())
                cmboxAccessLevel->setCurrentIndex(0);
            flt->addRow("Access level:", cmboxAccessLevel);
            QDateTimeEdit *dtedt = new QDateTimeEdit;
              dtedt->setMinimumDateTime(QDateTime::currentDateTime().addDays(1));
              dtedt->setDateTime(QDateTime::currentDateTime().addDays(3));
              dtedt->setDisplayFormat("dd MMMM yyyy hh:mm");
              dtedt->setCalendarPopup(true);
            flt->addRow(tr("Expiration date:", "lbl text"), dtedt);
            QSpinBox *sbox = new QSpinBox;
              sbox->setMinimum(1);
              sbox->setMaximum(USHRT_MAX);
              sbox->setValue(1);
            flt->addRow(tr("Count:", "lbl text"), sbox);
            QMap<TService, QCheckBox *> cboxMap;
            foreach (const TService &service, TServiceList::allServices()) {
                QCheckBox *cbox = new QCheckBox;
                  cbox->setEnabled(availableServices.contains(service));
                flt->addRow(tr("Access to", "lbl text") + " " + service.toString() + ":", cbox);
                cboxMap.insert(service, cbox);
            }
          vlt->addLayout(flt);
          QGroupBox *gbox = new QGroupBox(tr("Groups", "gbox title"));
            QHBoxLayout *hlt = new QHBoxLayout(gbox);
              TListWidget *lstwgt = new TListWidget;
                lstwgt->setButtonsVisible(true);
                lstwgt->setReadOnly(true);
                if (lstwgt) {
                    QList<TListWidget::Item> list;
                    foreach (const TGroupInfo &group, availableGroups) {
                        TListWidget::Item item;
                        item.text = group.name();
                        item.data = group.id();
                        list << item;
                    }
                    lstwgt->setAvailableItems(list);
                }
              hlt->addWidget(lstwgt);
          vlt->addWidget(gbox);
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()));
      dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
    if (dlg.exec() != QDialog::Accepted)
        return;
    TServiceList services;
    foreach (const TService &service, cboxMap.keys())
        if (cboxMap.value(service)->isChecked())
            services << service;
    TIdList groups;
    foreach (int i, bRangeD(0, lstwgt->itemCount() - 1))
        groups << lstwgt->itemData(i).toULongLong();
    TGenerateInvitesRequestData data;
    data.setAccessLevel(cmboxAccessLevel->itemData(cmboxAccessLevel->currentIndex()).toInt());
    data.setCount(quint16(sbox->value()));
    data.setExpirationDateTime(dtedt->dateTime());
    data.setGroups(groups);
    data.setServices(services);
    if (!data.isValid())
        return;
    TReply r = generateInvitesFunction(data, q_func());
    if (!r) {
        QMessageBox msg(q_func());
        msg.setWindowTitle(tr("Generating invites failed", "msgbox windowTitle"));
        msg.setIcon(QMessageBox::Critical);
        msg.setText(tr("Failed to generate invites. The following error occured:", "msgbox text"));
        msg.setInformativeText(r.messageString());
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
    }
}

void TInviteWidgetPrivate::selectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    bool b = !selected.isEmpty();
    actCopy->setEnabled(b);
    actDelete->setEnabled(b && deleteInvitesFunction);
}

/*============================================================================
================================ TInviteWidget ===============================
============================================================================*/

/*============================== Public constructors =======================*/

TInviteWidget::TInviteWidget(TInviteModel *model, const TAccessLevel &accessLevel, QWidget *parent) :
    QWidget(parent), BBaseObject(*new TInviteWidgetPrivate(this, model, accessLevel))
{
    d_func()->init();
}

TInviteWidget::~TInviteWidget()
{
    //
}

/*============================== Public methods ============================*/

TGroupInfoList TInviteWidget::availableGroups() const
{
    return d_func()->availableGroups;
}

TServiceList TInviteWidget::availableServices() const
{
    return d_func()->availableServices;
}

TInviteWidget::DeleteInvitesFunction TInviteWidget::deleteInvitesFunction() const
{
    return d_func()->deleteInvitesFunction;
}

TInviteWidget::GenerateInvitesFunction TInviteWidget::generateInvitesFunction() const
{
    return d_func()->generateInvitesFunction;
}

void TInviteWidget::setAvailableGroups(const TGroupInfoList &groups)
{
    d_func()->availableGroups = groups;
    bRemoveDuplicates(d_func()->availableGroups);
}

void TInviteWidget::setAvailableServices(const TServiceList &services)
{
    d_func()->availableServices = services;
    bRemoveDuplicates(d_func()->availableServices);
}

void TInviteWidget::setDeleteInvitesFunction(DeleteInvitesFunction deleteInvitesFunction)
{
    d_func()->deleteInvitesFunction = deleteInvitesFunction;
    d_func()->actDelete->setEnabled(deleteInvitesFunction && d_func()->view->selectionModel()->hasSelection());
}

void TInviteWidget::setGenerateInvitesFunction(GenerateInvitesFunction generateInvitesFunction)
{
    d_func()->generateInvitesFunction = generateInvitesFunction;
    d_func()->actGenerate->setEnabled(generateInvitesFunction
                                      && d_func()->AccessLevel >= TAccessLevel(TAccessLevel::ModeratorLevel));
}
