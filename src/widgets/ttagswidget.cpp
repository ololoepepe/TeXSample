#include "ttagswidget.h"
#include "ttagswidget_p.h"

#include <TeXSampleCore/TSampleInfo>

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>

#include <QAction>
#include <QHBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QList>
#include <QMenu>
#include <QSignalMapper>
#include <QString>
#include <QStringList>
#include <QToolButton>
#include <QWidget>

/*============================================================================
================================ TTagsWidgetPrivate ==========================
============================================================================*/

/*============================== Public constructors =======================*/

TTagsWidgetPrivate::TTagsWidgetPrivate(TTagsWidget *q) :
    BBaseObjectPrivate(q)
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
    QWidget(parent), BBaseObject(*new TTagsWidgetPrivate(this))
{
    d_func()->init();
}

TTagsWidget::~TTagsWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TTagsWidget::TTagsWidget(TTagsWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

QStringList TTagsWidget::availableTags() const
{
    QStringList list = tags();
    foreach (QAction *act, d_func()->tbtn->menu()->actions())
        list << act->text();
    list.removeAll("");
    list.removeDuplicates();
    return list;
}

bool TTagsWidget::isReadOnly() const
{
    return d_func()->ledt->isReadOnly();
}

void TTagsWidget::setAvailableTags(const QStringList &list)
{
    d_func()->tbtn->menu()->clear();
    QStringList nlist = list;
    nlist.removeAll("");
    nlist.removeDuplicates();
    while (nlist.size() > 20)
        nlist.removeFirst();
    foreach (const QString &tag, nlist) {
        QAction *act = d_func()->tbtn->menu()->addAction(tag);
        bSetMapping(d_func()->mpr, act, SIGNAL(triggered()), tag);
    }
    d_func()->tbtn->setEnabled(!isReadOnly() && !d_func()->tbtn->menu()->isEmpty());
}

void TTagsWidget::setReadOnly(bool ro)
{
    d_func()->ledt->setReadOnly(ro);
    d_func()->tbtn->setEnabled(!ro);
}

void TTagsWidget::setTags(const QStringList &list)
{
    d_func()->ledt->setText(TSampleInfo::listToString(list));
}

QStringList TTagsWidget::tags() const
{
    return TSampleInfo::listFromString(d_func()->ledt->text());
}
