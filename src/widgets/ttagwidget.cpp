/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleWidgets module of the TeXSample library.
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

#include "ttagwidget.h"
#include "ttagwidget_p.h"

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>

#include <QAction>
#include <QHBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QList>
#include <QMenu>
#include <QRegExp>
#include <QSignalMapper>
#include <QSize>
#include <QString>
#include <QStringList>
#include <QToolButton>
#include <QWidget>

/*============================================================================
================================ TTagWidgetPrivate ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TTagWidgetPrivate::TTagWidgetPrivate(TTagWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TTagWidgetPrivate::~TTagWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TTagWidgetPrivate::init()
{
    mpr = new QSignalMapper(this);
    connect(mpr, SIGNAL(mapped(QString)), this, SLOT(addTag(QString)));
    //
    QHBoxLayout *hlt = new QHBoxLayout(q_func());
      hlt->setContentsMargins(0, 0, 0, 0);
      ledt = new QLineEdit;
      hlt->addWidget(ledt);
      QSize sz(ledt->sizeHint().height(), ledt->sizeHint().height());
      tbtn = new QToolButton;
        tbtn->setMenu(new QMenu);
        tbtn->setPopupMode(QToolButton::InstantPopup);
        tbtn->setIconSize(sz - (tbtn->sizeHint() - tbtn->iconSize()));
        tbtn->setIcon(BApplication::icon("flag"));
        tbtn->setFixedSize(sz);
        tbtn->setToolTip(tr("Add tag...", "tbtn toolTip"));
        tbtn->setEnabled(false);
      hlt->addWidget(tbtn);
}

/*============================== Public slots ==============================*/

void TTagWidgetPrivate::addTag(const QString &tag)
{
    q_func()->setTags(q_func()->tags() << tag);
}

/*============================================================================
================================ TTagWidget ==================================
============================================================================*/

/*============================== Public constructors =======================*/

TTagWidget::TTagWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TTagWidgetPrivate(this))
{
    d_func()->init();
}

TTagWidget::~TTagWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TTagWidget::TTagWidget(TTagWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

QStringList TTagWidget::availableTags() const
{
    QStringList list = tags();
    foreach (QAction *act, d_func()->tbtn->menu()->actions())
        list << act->text();
    list.removeAll("");
    list.removeDuplicates();
    return list;
}

bool TTagWidget::buttonsVisible() const
{
    return d_func()->tbtn->isVisible();
}

bool TTagWidget::isReadOnly() const
{
    return d_func()->ledt->isReadOnly();
}

void TTagWidget::setAvailableTags(const QStringList &list)
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

void TTagWidget::setButtonsVisible(bool b)
{
    d_func()->tbtn->setVisible(b);
}

void TTagWidget::setReadOnly(bool ro)
{
    d_func()->ledt->setReadOnly(ro);
    d_func()->tbtn->setEnabled(!ro);
}

void TTagWidget::setTags(const QStringList &list)
{
    d_func()->ledt->setText(list.join(", "));
}

QStringList TTagWidget::tags() const
{
    return d_func()->ledt->text().split(QRegExp("\\,\\s*"), QString::SkipEmptyParts);
}
