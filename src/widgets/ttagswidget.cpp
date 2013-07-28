#include "ttagswidget.h"
#include "ttagswidget_p.h"

#include <TeXSampleCore/TSampleInfo>

#include <BeQtGlobal>
#include <BBase>
#include <BeQtCore/private/bbase_p.h>
#include <BApplication>

#include <QWidget>
#include <QSignalMapper>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QList>
#include <QString>
#include <QStringList>

/*============================================================================
================================ TTagsWidgetPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TTagsWidgetPrivate::TTagsWidgetPrivate(TTagsWidget *q) :
    BBasePrivate(q)
{
    //
}

TTagsWidgetPrivate::~TTagsWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TTagsWidgetPrivate::init()
{
    mpr = new QSignalMapper(this);
    connect(mpr, SIGNAL(mapped(QString)), this, SLOT(addTag(QString)));
    //
    QHBoxLayout *hlt = new QHBoxLayout(q_func());
      hlt->setContentsMargins(0, 0, 0, 0);
      ledt = new QLineEdit;
      hlt->addWidget(ledt);
      tbtn = new QToolButton;
        tbtn->setMenu(new QMenu);
        tbtn->setPopupMode(QToolButton::InstantPopup);
        tbtn->setIcon(BApplication::icon("flag"));
        tbtn->setToolTip(tr("Add tag...", "tbtn toolTip"));
        tbtn->setEnabled(false);
      hlt->addWidget(tbtn);
}

/*============================== Public slots ==============================*/

void TTagsWidgetPrivate::addTag(const QString &tag)
{
    q_func()->setTags(q_func()->tags() << tag);
}

/*============================================================================
================================ TTagsWidget =================================
============================================================================*/

/*============================== Public constructors =======================*/

TTagsWidget::TTagsWidget(QWidget *parent) :
    QWidget(parent), BBase(*new TTagsWidgetPrivate(this))
{
    d_func()->init();
}

TTagsWidget::~TTagsWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TTagsWidget::TTagsWidget(TTagsWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBase(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

void TTagsWidget::setAvailableTags(const QStringList &list)
{
    d_func()->tbtn->menu()->clear();
    QStringList nlist = list;
    nlist.removeAll("");
    nlist.removeDuplicates();
    while (nlist.size() > 20)
        nlist.removeFirst();
    foreach (const QString &tag, nlist)
    {
        QAction *act = d_func()->tbtn->menu()->addAction(tag);
        bSetMapping(d_func()->mpr, act, SIGNAL(triggered()), tag);
    }
    d_func()->tbtn->setEnabled(!isReadOnly() && !d_func()->tbtn->menu()->isEmpty());
}

void TTagsWidget::setTags(const QStringList &list)
{
    d_func()->ledt->setText(TSampleInfo::listToString(list));
}

void TTagsWidget::setReadOnly(bool ro)
{
    d_func()->ledt->setReadOnly(ro);
    d_func()->tbtn->setEnabled(!ro);
}

QStringList TTagsWidget::availableTags() const
{
    QStringList list = tags();
    foreach (QAction *act, d_func()->tbtn->menu()->actions())
        list << act->text();
    list.removeAll("");
    list.removeDuplicates();
    return list;
}

QStringList TTagsWidget::tags() const
{
    return TSampleInfo::listFromString(d_func()->ledt->text());
}

bool TTagsWidget::isReadOnly() const
{
    return d_func()->ledt->isReadOnly();
}
