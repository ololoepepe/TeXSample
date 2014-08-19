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

#include "tauthorinfolistwidgetitemdelegate.h"
#include "tauthorinfolistwidgetitemdelegate_p.h"

#include "tabstractlistwidgetitemdelegate.h"
#include "tauthorinfowidget.h"
#include "tlistwidget.h"

#include <TeXSampleCore/TAuthorInfo>

#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>

#include <QDialogButtonBox>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QStyleOptionViewItem>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

/*============================================================================
================================ TAuthorInfoListWidgetItemDelegatePrivate ====
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorInfoListWidgetItemDelegatePrivate::TAuthorInfoListWidgetItemDelegatePrivate(
        TAuthorInfoListWidgetItemDelegate *q) :
    BBaseObjectPrivate(q)
{
    //
}

TAuthorInfoListWidgetItemDelegatePrivate::~TAuthorInfoListWidgetItemDelegatePrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorInfoListWidgetItemDelegatePrivate::init()
{
    //
}

/*============================================================================
================================ TAuthorInfoDelegateWidget ===================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorInfoDelegateWidget::TAuthorInfoDelegateWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *vlt = new QVBoxLayout(this);
    mauthorInfoWidget = new TAuthorInfoWidget;
    vlt->addWidget(mauthorInfoWidget);
    QDialogButtonBox *dlgbbox = new QDialogButtonBox;
    btnAccept = dlgbbox->addButton(QDialogButtonBox::Ok);
    btnAccept->setEnabled(mauthorInfoWidget->hasValidInput());
    connect(mauthorInfoWidget, SIGNAL(inputValidityChanged(bool)), btnAccept, SLOT(setEnabled(bool)));
    btnReject = dlgbbox->addButton(QDialogButtonBox::Cancel);
    vlt->addWidget(dlgbbox);
}

/*============================== Public methods ============================*/

TAuthorInfoWidget *TAuthorInfoDelegateWidget::authorInfoWidget()
{
    return mauthorInfoWidget;
}

/*============================== Private slots =============================*/

void TAuthorInfoDelegateWidget::accepted()
{
    Q_EMIT commitDataAndCloseEditor(this);
}

void TAuthorInfoDelegateWidget::rejected()
{
    Q_EMIT closeEditor(this);
}

/*============================================================================
================================ TAuthorInfoListWidgetItemDelegate ===========
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorInfoListWidgetItemDelegate::TAuthorInfoListWidgetItemDelegate(QObject *parent) :
    TAbstractListWidgetItemDelegate(parent), BBaseObject(*new TAuthorInfoListWidgetItemDelegatePrivate(this))
{
    d_func()->init();
}

TAuthorInfoListWidgetItemDelegate::~TAuthorInfoListWidgetItemDelegate()
{
    //
}

/*============================== Static public methods =====================*/

bool TAuthorInfoListWidgetItemDelegate::testItemEquality(const TListWidget::Item &item1,
                                                         const TListWidget::Item &item2)
{
    TAuthorInfo info1 = item1.data.value<TAuthorInfo>();
    TAuthorInfo info2 = item2.data.value<TAuthorInfo>();
    if (info1.isValid() && info2.isValid())
        return info1 == info2;
    else if (!info1.isValid() && !info2.isValid())
        return true;
    else
        return false;
}

/*============================== Public methods ============================*/

QWidget *TAuthorInfoListWidgetItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &) const
{
    TAuthorInfoDelegateWidget *wgt = new TAuthorInfoDelegateWidget(parent);
    connect(wgt, SIGNAL(closeEditor(QWidget *)), this, SIGNAL(closeEditor(QWidget *)));
    connect(wgt, SIGNAL(commitDataAndCloseEditor(QWidget *)), this, SIGNAL(commitDataAndCloseEditor(QWidget *)));
    return wgt;
}

void TAuthorInfoListWidgetItemDelegate::setEditorData(QWidget *editor, const QString &, const QVariant &data) const
{
    TAuthorInfoDelegateWidget *wgt = dynamic_cast<TAuthorInfoDelegateWidget *>(editor);
    if (!wgt)
        return;
    wgt->authorInfoWidget()->setInfo(data.value<TAuthorInfo>());
}

void TAuthorInfoListWidgetItemDelegate::setModelData(QWidget *editor, QString &text, QVariant &data) const
{
    TAuthorInfoDelegateWidget *wgt = dynamic_cast<TAuthorInfoDelegateWidget *>(editor);
    if (!wgt)
        return;
    TAuthorInfo info = wgt->authorInfoWidget()->info();
    data = info;
    text = info.name() + (!info.patronymic().isEmpty() ? " " : "") + info.patronymic()
            + (!info.surname().isEmpty() ? " " : "") + info.surname();
}
