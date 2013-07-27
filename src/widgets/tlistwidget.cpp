#include "tlistwidget.h"
#include "tlistwidget_p.h"

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BApplication>

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QStringList>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QSignalMapper>

/*============================================================================
================================ TListWidgetPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TListWidgetPrivate::TListWidgetPrivate(TListWidget *q) :
    BBasePrivate(q)
{
    //
}

TListWidgetPrivate::~TListWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TListWidgetPrivate::init()
{
    readOnly = false;
    mpr = new QSignalMapper(this);
    connect(mpr, SIGNAL(mapped(QString)), this, SLOT(addItem(QString)));
    //
    QHBoxLayout *hlt = new QHBoxLayout(q_func());
      lstwgt = new QListWidget;
        lstwgt->setEditTriggers(QListWidget::EditKeyPressed | QListWidget::DoubleClicked);
        connect(lstwgt, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(addItem()));
        connect(lstwgt, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
                this, SLOT(lstwgtCurrentItemChanged(QListWidgetItem *)));
      hlt->addWidget(lstwgt);
      QVBoxLayout *vlt = new QVBoxLayout;
        tbtnAdd = new QToolButton;
          tbtnAdd->setMenu(new QMenu);
          tbtnAdd->setPopupMode(QToolButton::InstantPopup);
          tbtnAdd->setEnabled(false);
          tbtnAdd->setIcon(BApplication::icon("edit_add"));
          tbtnAdd->setToolTip(tr("Add...", "tbtnt toolTip"));
        vlt->addWidget(tbtnAdd);
        QHBoxLayout *hltw = new QHBoxLayout;
          tbtnRemove = new QToolButton;
            tbtnRemove->setEnabled(false);
            tbtnRemove->setIcon(BApplication::icon("editdelete"));
            tbtnRemove->setToolTip(tr("Remove selected", "tbtnt toolTip"));
            connect(tbtnRemove, SIGNAL(clicked()), this, SLOT(removeSelectedItem()));
          hltw->addWidget(tbtnRemove);
          tbtnClear = new QToolButton;
            tbtnClear->setEnabled(false);
            tbtnClear->setIcon(BApplication::icon("editclear"));
            tbtnClear->setToolTip(tr("Clear list", "tbtnt toolTip"));
            connect(tbtnClear, SIGNAL(clicked()), this, SLOT(clearList()));
          hltw->addWidget(tbtnClear);
        vlt->addLayout(hltw);
        hltw = new QHBoxLayout;
          tbtnUp = new QToolButton;
            tbtnUp->setIcon(BApplication::icon("1uparrow"));
            tbtnUp->setToolTip(tr("Move up", "tbtnt toolTip"));
            connect(tbtnUp, SIGNAL(clicked()), this, SLOT(moveItemUp()));
          hltw->addWidget(tbtnUp);
          tbtnDown = new QToolButton;
            tbtnDown->setIcon(BApplication::icon("1downarrow"));
            tbtnDown->setToolTip(tr("Move down", "tbtnt toolTip"));
            connect(tbtnDown, SIGNAL(clicked()), this, SLOT(moveItemDown()));
          hltw->addWidget(tbtnDown);
        vlt->addLayout(hltw);
      hlt->addLayout(vlt);
      //
    addItem();
    lstwgtCurrentItemChanged(lstwgt->currentItem());
}

/*============================== Public slots ==============================*/

void TListWidgetPrivate::addItem(const QString &text)
{
    if (text.isEmpty())
    {
        QListWidgetItem *lwi = lstwgt->item(lstwgt->count() - 1);
        if (lwi && lwi->text().isEmpty())
            return;
    }
    if (!text.isEmpty() && q_func()->items().contains(text))
        return;
    QListWidgetItem *lwi = new QListWidgetItem(text);
    if (!q_func()->isReadOnly())
        lwi->setFlags(lwi->flags () | Qt::ItemIsEditable);
    int ind = lstwgt->count();
    if (!text.isEmpty() && ind && lstwgt->item(ind - 1)->text().isEmpty())
        --ind;
    lstwgt->insertItem(ind, lwi);
    if (!q_func()->isReadOnly() && text.isEmpty())
        lstwgt->setCurrentItem(lwi);
}

void TListWidgetPrivate::removeSelectedItem()
{
    delete lstwgt->takeItem(lstwgt->currentRow());
}

void TListWidgetPrivate::clearList()
{
    lstwgt->clear();
    if (!q_func()->isReadOnly())
        addItem();
}

void TListWidgetPrivate::moveItemUp()
{
    int ind = lstwgt->currentRow();
    if (!ind)
        return;
    QListWidgetItem *lwi = lstwgt->takeItem(ind);
    if (!lwi)
        return;
    lstwgt->insertItem(ind - 1, lwi);
    lstwgt->setCurrentItem(lwi);
}

void TListWidgetPrivate::moveItemDown()
{
    int ind = lstwgt->currentRow();
    if (ind == lstwgt->count() - 1)
        return;
    QListWidgetItem *lwi = lstwgt->takeItem(ind);
    if (!lwi)
        return;
    lstwgt->insertItem(ind + 1, lwi);
    lstwgt->setCurrentItem(lwi);
}

void TListWidgetPrivate::lstwgtCurrentItemChanged(QListWidgetItem *current)
{
    tbtnRemove->setEnabled(current && current != lstwgt->item(lstwgt->count() - 1));
    tbtnClear->setEnabled(lstwgt->count() > 1);
    tbtnUp->setEnabled(current && current != lstwgt->item(lstwgt->count() - 1) && current != lstwgt->item(0));
    tbtnDown->setEnabled(current && current != lstwgt->item(lstwgt->count() - 1)
            && current != lstwgt->item(lstwgt->count() - 2));
}

/*============================================================================
================================ TListWidget =================================
============================================================================*/

/*============================== Public constructors =======================*/

TListWidget::TListWidget(QWidget *parent) :
    QWidget(parent), BBase(*new TListWidgetPrivate(this))
{
    d_func()->init();
}

TListWidget::~TListWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TListWidget::TListWidget(TListWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

void TListWidget::setReadOnly(bool ro)
{
    if (ro == d_func()->readOnly)
        return;
    d_func()->readOnly = ro;
    setItems(items());
}

void TListWidget::setButtonsVisible(bool b)
{
    d_func()->tbtnAdd->setVisible(b);
    d_func()->tbtnRemove->setVisible(b);
    d_func()->tbtnClear->setVisible(b);
    d_func()->tbtnUp->setVisible(b);
    d_func()->tbtnDown->setVisible(b);
}

void TListWidget::setAvailableItems(const QStringList &items)
{
    d_func()->tbtnAdd->menu()->clear();
    QStringList list = items;
    list.removeAll("");
    list.removeDuplicates();
    while (list.size() > 20)
        list.removeFirst();
    foreach (const QString &s, list)
    {
        QAction *act = d_func()->tbtnAdd->menu()->addAction(s);
        bSetMapping(d_func()->mpr, act, SIGNAL(triggered()), s);
    }
    d_func()->tbtnAdd->setEnabled(!isReadOnly() && !d_func()->tbtnAdd->menu()->isEmpty());
}

void TListWidget::setItems(const QStringList &list)
{
    d_func()->lstwgt->clear();
    foreach (const QString &s, list)
        d_func()->addItem(s);
    if (!isReadOnly())
        d_func()->addItem();
}

void TListWidget::clear()
{
    setItems(QStringList());
}

bool TListWidget::isReadOnly() const
{
    return d_func()->readOnly;
}

bool TListWidget::areButtonsVisible() const
{
    return d_func()->tbtnAdd->isVisible();
}

QStringList TListWidget::availableItems() const
{
    QStringList list = items();
    foreach (QAction *act, d_func()->tbtnAdd->menu()->actions())
        list << act->text();
    list.removeAll("");
    list.removeDuplicates();
    while (list.size() > 20)
        list.removeFirst();
    return list;
}

QStringList TListWidget::items() const
{
    QStringList list;
    foreach (int i, bRangeD(0, d_func()->lstwgt->count() - 1))
        list << d_func()->lstwgt->item(i)->text();
    list.removeAll("");
    list.removeDuplicates();
    return list;
}
