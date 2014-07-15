#include "tgroupwidget.h"
#include "tgroupwidget_p.h"

#include <TeXSampleCore/TAddGroupRequestData>
#include <TeXSampleCore/TDeleteGroupRequestData>
#include <TeXSampleCore/TEditGroupRequestData>
#include <TeXSampleCore/TGroupInfo>
#include <TeXSampleCore/TGroupModel>
#include <TeXSampleCore/TReply>

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
        actAdd = tbar->addAction(BApplication::icon("edit_add"), tr("Generate group...", "act text"),
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
    if (!addGroupFunction)
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
    TReply r = addGroupFunction(data, q_func());
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
}

void TGroupWidgetPrivate::deleteGroup()
{
    if (!deleteGroupFunction)
        return;
    QModelIndex index = view->selectionModel()->currentIndex();
    if (!index.isValid())
        return;
    const TGroupInfo *info = Model->groupInfoAt(index.row());
    if (!info)
        return;
    TDeleteGroupRequestData data;
    data.setId(info->id());
    TReply r = deleteGroupFunction(data, q_func());
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
}

void TGroupWidgetPrivate::editGroup(const QModelIndex &index)
{
    if (!addGroupFunction)
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
    TReply r = editGroupFunction(data, q_func());
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
}

void TGroupWidgetPrivate::selectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    bool b = !selected.isEmpty();
    actEdit->setEnabled(b && editGroupFunction);
    actDelete->setEnabled(b && deleteGroupFunction);
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

TGroupWidget::AddGroupFunction TGroupWidget::addGroupFunction() const
{
    return d_func()->addGroupFunction;
}

TGroupWidget::DeleteGroupFunction TGroupWidget::deleteGroupFunction() const
{
    return d_func()->deleteGroupFunction;
}

TGroupWidget::EditGroupFunction TGroupWidget::editGroupFunction() const
{
    return d_func()->editGroupFunction;
}

void TGroupWidget::setAddGroupFunction(AddGroupFunction addGroupFunction)
{
    d_func()->addGroupFunction = addGroupFunction;
    d_func()->actAdd->setEnabled(addGroupFunction);
}

void TGroupWidget::setDeleteGroupFunction(DeleteGroupFunction deleteGroupFunction)
{
    d_func()->deleteGroupFunction = deleteGroupFunction;
    d_func()->actDelete->setEnabled(deleteGroupFunction && d_func()->view->selectionModel()->hasSelection());
}

void TGroupWidget::setEditGroupFunction(EditGroupFunction editGroupFunction)
{
    d_func()->editGroupFunction = editGroupFunction;
    d_func()->actEdit->setEnabled(editGroupFunction && d_func()->view->selectionModel()->hasSelection());
}
