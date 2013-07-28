#include "tinvitesdialog.h"
#include "tinvitesdialog_p.h"
#include "tlistwidget.h"

#include <TeXSample>
#include <TInviteInfo>
#include <TOperationResult>
#include <TService>
#include <TServiceList>

#include <BeQt>
#include <BDialog>
#include <BApplication>

#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolBar>
#include <QAction>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVariant>
#include <QMessageBox>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QString>
#include <QClipboard>
#include <QApplication>
#include <QToolTip>
#include <QPoint>
#include <QSpinBox>
#include <QCheckBox>
#include <QHeaderView>
#include <QMap>
#include <QGroupBox>

/*============================================================================
================================ TInvitesDialogPrivate =======================
============================================================================*/

/*============================== Public constructors =======================*/

TInvitesDialogPrivate::TInvitesDialogPrivate(TInvitesDialog *q, TestServiceFunction testf, GetInvitesFunction getf,
                                             GenerateInvitesFunction genf, GenerateInvitesClabFunction gencf) :
    BDialogPrivate(q), TestFunction(testf), GetFunction(getf), GenerateFunction(genf), GenerateClabFunction(gencf)
{
    //
}

TInvitesDialogPrivate::~TInvitesDialogPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TInvitesDialogPrivate::init()
{
    clab = false;
    //
    B_Q(TInvitesDialog);
    q->setWindowTitle(tr("Invites management", "windowTitle"));
    QWidget *wgt = new QWidget;
      QVBoxLayout *vlt = new QVBoxLayout(wgt);
        tblwgt = new QTableWidget(0, 2);
        QStringList headers;
        headers << tr("Expiration date", "tblwgt header");
        headers << tr("Available services", "tblwgt header");
        tblwgt->setHorizontalHeaderLabels(headers);
        tblwgt->setAlternatingRowColors(true);
        tblwgt->setEditTriggers(QTableView::NoEditTriggers);
        tblwgt->setSelectionBehavior(QTableWidget::SelectRows);
        tblwgt->setSelectionMode(QTableView::SingleSelection);
        tblwgt->horizontalHeader()->setStretchLastSection(true);
        tblwgt->verticalHeader()->setVisible(false);
        connect(tblwgt, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(copyInvite(QTableWidgetItem *)));
        connect(tblwgt, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)),
                this, SLOT(tblwgtCurrentItemChanged(QTableWidgetItem *)));
        vlt->addWidget(tblwgt);
        tbar = new QToolBar;
          tbar->addAction(BApplication::icon("edit_add"), tr("Generate invites...", "act text"),
                          this, SLOT(generateInvite()));
          actCopy = tbar->addAction(BApplication::icon("editcopy"), tr("Copy selected invite code to clipboard",
                                                                       "act text"), this, SLOT(copyInvite()));
            actCopy->setEnabled(false);
        vlt->addWidget(tbar);
      q->setWidget(wgt);
    q->addButton(QDialogButtonBox::Close, SLOT(close()));
    q->resize(450, q->height());
    //
    updateInvitesList();
}

/*============================== Public slots ==============================*/

void TInvitesDialogPrivate::generateInvite()
{
    BDialog dlg(q_func());
    dlg.setWindowTitle(tr("Generating invites", "dlg windowTitle"));
      QWidget *wgt = new QWidget;
        QVBoxLayout *vlt = new QVBoxLayout(wgt);
          QFormLayout *flt = new QFormLayout;
            QDateTimeEdit *dtedt = new QDateTimeEdit;
              dtedt->setMinimumDateTime(QDateTime::currentDateTime().addDays(1));
              dtedt->setMaximumDateTime(QDateTime::currentDateTime().addMonths(1));
              dtedt->setDateTime(QDateTime::currentDateTime().addDays(3));
              dtedt->setDisplayFormat("dd MMMM yyyy hh:mm:ss");
              dtedt->setCalendarPopup(true);
            flt->addRow(tr("Expiration date:", "lbl text"), dtedt);
            QSpinBox *sbox = new QSpinBox;
              sbox->setMinimum(1);
              sbox->setMaximum(Texsample::MaximumInvitesCount);
              sbox->setValue(1);
            flt->addRow(tr("Count:", "lbl text"), sbox);
            QMap<TService, QCheckBox *> cboxMap;
            foreach (const TService &s, TServiceList::allServices())
            {
                QCheckBox *cbox = new QCheckBox;
                  cbox->setEnabled(TestFunction(s));
                flt->addRow(tr("Access to", "lbl text") + " " + s.toString() + ":", cbox);
                cboxMap.insert(s, cbox);
            }
          vlt->addLayout(flt);
          TListWidget *lstwgt = 0;
          if (clab)
          {
              QGroupBox *gbox = new QGroupBox(tr("CLab groups", "gbox title"));
                QHBoxLayout *hlt = new QHBoxLayout(gbox);
                  lstwgt = new TListWidget;
                    lstwgt->setButtonsVisible(true);
                    lstwgt->setReadOnly(true);
                    lstwgt->setAvailableItems(clabGroups);
                  hlt->addWidget(lstwgt);
              vlt->addWidget(gbox);
          }
      dlg.setWidget(wgt);
      dlg.addButton(QDialogButtonBox::Ok, SLOT(accept()));
      dlg.addButton(QDialogButtonBox::Cancel, SLOT(reject()));
    if (dlg.exec() != QDialog::Accepted)
        return;
    TServiceList services;
    foreach (const TService &s, cboxMap.keys())
        if (cboxMap.value(s)->isChecked())
            services << s;
    TInviteInfoList invites;
    TOperationResult r;
    if (lstwgt)
        r = GenerateClabFunction(invites, dtedt->dateTime().toUTC(), sbox->value(), services, lstwgt->items(),
                                 q_func());
    else
        r = GenerateFunction(invites, dtedt->dateTime().toUTC(), sbox->value(), services, q_func());
    if (!r)
    {
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
    updateInvitesList(invites);
}

void TInvitesDialogPrivate::copyInvite(QTableWidgetItem *item)
{
    if (!item)
        item = tblwgt->currentItem();
    if (!item)
        return;
    QApplication::clipboard()->setText(item->toolTip());
    BeQt::waitNonBlocking(100);
    QToolTip::showText(tblwgt->mapToGlobal(tblwgt->visualItemRect(item).topLeft()),
                       tr("Invite was copied to clipboard", "toolTip"), tbar);
}

void TInvitesDialogPrivate::updateInvitesList(TInviteInfoList list)
{
    if (list.isEmpty())
    {
        TOperationResult r = GetFunction(list, q_func());
        if (!r)
        {
            QMessageBox msg(q_func());
            msg.setWindowTitle(tr("Updating invites list failed", "msgbox windowTitle"));
            msg.setIcon(QMessageBox::Critical);
            msg.setText(tr("Failed to update invites list. The following error occured:", "msgbox text"));
            msg.setInformativeText(r.messageString());
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Ok);
            msg.exec();
        }
        tblwgt->clearContents();
        tblwgt->setRowCount(0);
    }
    foreach (const TInviteInfo &inv, list)
    {
        tblwgt->insertRow(tblwgt->rowCount());
        QTableWidgetItem *twi = new QTableWidgetItem;
        twi->setText(inv.expirationDateTime(Qt::LocalTime).toString("dd MMMM yyyy hh:mm:ss"));
        twi->setToolTip(inv.codeString());
        tblwgt->setItem(tblwgt->rowCount() - 1, 0, twi);
        twi = new QTableWidgetItem;
        twi->setText(inv.services().toString());
        twi->setToolTip(inv.codeString());
        tblwgt->setItem(tblwgt->rowCount() - 1, 1, twi);
    }
    if (tblwgt->rowCount())
        tblwgt->setCurrentCell(tblwgt->rowCount() - 1, 0);
}

void TInvitesDialogPrivate::tblwgtCurrentItemChanged(QTableWidgetItem *current)
{
    actCopy->setEnabled(current);
    copyInvite();
}

/*============================================================================
================================ TInvitesDialog ==============================
============================================================================*/

/*============================== Public constructors =======================*/

TInvitesDialog::TInvitesDialog(TestServiceFunction testf, GetInvitesFunction getf, GenerateInvitesFunction genf,
                               QWidget *parent) :
    BDialog(*new TInvitesDialogPrivate(this, testf, getf, genf), parent)
{
    d_func()->init();
}

TInvitesDialog::TInvitesDialog(TestServiceFunction testf, GetInvitesFunction getf, GenerateInvitesClabFunction genf,
                               QWidget *parent) :
    BDialog(*new TInvitesDialogPrivate(this, testf, getf, 0, genf), parent)
{
    d_func()->init();
}

TInvitesDialog::~TInvitesDialog()
{
    //
}

/*============================== Public methods ============================*/

void TInvitesDialog::setClabEnabled(bool b)
{
    d_func()->clab = b;
}

void TInvitesDialog::setAvailableClabGroups(const QStringList &list)
{
    d_func()->clabGroups = list;
}

bool TInvitesDialog::isClabEnabled() const
{
    return d_func()->clab;
}

QStringList TInvitesDialog::availableClabGroups() const
{
    return d_func()->clabGroups;
}
