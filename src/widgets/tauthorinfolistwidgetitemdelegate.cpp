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

#include <QDebug>
#include <QDialogButtonBox>
#include <QEvent>
#include <QKeyEvent>
#include <QMetaObject>
#include <QObject>
#include <QPushButton>
#include <QResizeEvent>
#include <QSize>
#include <QString>
#include <QStyleOptionViewItem>
#include <QTimer>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

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
    btnAccept->setDefault(true);
    connect(mauthorInfoWidget, SIGNAL(inputValidityChanged(bool)), btnAccept, SLOT(setEnabled(bool)));
    connect(btnAccept, SIGNAL(clicked()), this, SLOT(accepted()));
    btnReject = dlgbbox->addButton(QDialogButtonBox::Cancel);
    connect(btnReject, SIGNAL(clicked()), this, SLOT(rejected()));
    vlt->addWidget(dlgbbox);
    if (parent)
        parent->installEventFilter(this);
}

/*============================== Public methods ============================*/

TAuthorInfoWidget *TAuthorInfoDelegateWidget::authorInfoWidget()
{
    return mauthorInfoWidget;
}

bool TAuthorInfoDelegateWidget::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::Resize && parentWidget()) {
        QResizeEvent *re = static_cast<QResizeEvent *>(event);
        setFixedWidth(qMax(re->size().width() - 4, sizeHint().width()));
        setFixedHeight(qMin(re->size().height() - 4, sizeHint().height()));
    }
    return false;
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
    isAccepted = false;
}

/*============================== Public slots ==============================*/

void TAuthorInfoListWidgetItemDelegatePrivate::clearCurrent()
{
    isAccepted = false;
}

void TAuthorInfoListWidgetItemDelegatePrivate::commitDataAndCloseEditor(QWidget *editor)
{
    isAccepted = true;
    QMetaObject::invokeMethod(q_func(), "commitDataAndCloseEditor", Q_ARG(QWidget *, editor));
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
    TAuthorInfoListWidgetItemDelegatePrivate *d = const_cast<TAuthorInfoListWidgetItemDelegate *>(this)->d_func();
    connect(wgt, SIGNAL(closeEditor(QWidget *)), this, SIGNAL(closeEditor(QWidget *)));
    connect(wgt, SIGNAL(commitDataAndCloseEditor(QWidget *)), d, SLOT(commitDataAndCloseEditor(QWidget *)));
    if (parent) {
        wgt->setFixedWidth(qMax(parent->width() - 4, wgt->sizeHint().width()));
        wgt->setFixedHeight(qMin(parent->height() - 4, wgt->sizeHint().height()));
    }
    connect(wgt, SIGNAL(destroyed()), d, SLOT(clearCurrent()));
    const_cast<TAuthorInfoListWidgetItemDelegate *>(this)->d_func()->currentEditor = wgt;
    return wgt;
}

bool TAuthorInfoListWidgetItemDelegate::eventFilter(QObject *, QEvent *event)
{
    if (d_func()->currentEditor.isNull())
        return false;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return) {
            if (d_func()->currentEditor->authorInfoWidget()->hasValidInput())
                d_func()->commitDataAndCloseEditor(d_func()->currentEditor);
            return true;
        }
    }
    return false;
}

bool TAuthorInfoListWidgetItemDelegate::hideRowsWhenEditing() const
{
    return true;
}

QSize TAuthorInfoListWidgetItemDelegate::sizeHint(QWidget *editor, const QStyleOptionViewItem &option) const
{
    TAuthorInfoDelegateWidget *wgt = qobject_cast<TAuthorInfoDelegateWidget *>(editor);
    if (!wgt || !wgt->isVisible())
        return TAbstractListWidgetItemDelegate::sizeHint(editor, option);
    return wgt->size();
}

void TAuthorInfoListWidgetItemDelegate::setEditorData(QWidget *editor, const QString &, const QVariant &data) const
{
    TAuthorInfoDelegateWidget *wgt = qobject_cast<TAuthorInfoDelegateWidget *>(editor);
    if (!wgt)
        return;
    wgt->authorInfoWidget()->setInfo(data.value<TAuthorInfo>());
}

bool TAuthorInfoListWidgetItemDelegate::setModelData(QWidget *editor, QString &text, QVariant &data) const
{
    if (!d_func()->isAccepted)
        return false;
    TAuthorInfoDelegateWidget *wgt = qobject_cast<TAuthorInfoDelegateWidget *>(editor);
    if (!wgt)
        return false;
    TAuthorInfo info = wgt->authorInfoWidget()->info();
    if (!info.isValid())
        return false;
    data = info;
    text = info.name() + (!info.patronymic().isEmpty() ? " " : "") + info.patronymic()
            + (!info.surname().isEmpty() ? " " : "") + info.surname();
    return true;
}
