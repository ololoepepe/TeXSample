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

#include "tauthorinfowidget.h"
#include "tauthorinfowidget_p.h"

#include <TeXSampleCore/TAuthorInfo>
#include <TeXSampleCore/TeXSample>

#include <BApplication>
#include <BBaseObject>
#include <BeQtCore/private/bbaseobject_p.h>
#include <BGuiTools>
#include <BInputField>
#include <BLineEdit>

#include <QDebug>
#include <QFormLayout>
#include <QLabel>
#include <QMetaObject>
#include <QRegExp>
#include <QRegExpValidator>
#include <QString>
#include <QValidator>
#include <QWidget>

/*============================================================================
================================ TAuthorInfoWidgetPrivate ====================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorInfoWidgetPrivate::TAuthorInfoWidgetPrivate(TAuthorInfoWidget *q) :
    BBaseObjectPrivate(q)
{
    //
}

TAuthorInfoWidgetPrivate::~TAuthorInfoWidgetPrivate()
{
    //
}

/*============================== Public methods ============================*/

void TAuthorInfoWidgetPrivate::init()
{
    valid = false;
    flt = new QFormLayout(q_func());
    initLineEdit(ledtName, Texsample::MaximumNameLength, true);
    initLineEdit(ledtPatronymic, Texsample::MaximumPatronymicLength);
    initLineEdit(ledtSurname, Texsample::MaximumSurnameLength);
    initLineEdit(ledtOrganization, Texsample::MaximumOrganizationLength);
    initLineEdit(ledtPost, Texsample::MaximumPostLength);
    initLineEdit(ledtRole, Texsample::MaximumRoleLength);
    //
    retranslateUi();
    connect(bApp, SIGNAL(languageChanged()), this, SLOT(retranslateUi()));
}

void TAuthorInfoWidgetPrivate::initLineEdit(BLineEdit *&ledt, int maximimTextLength, bool required)
{
    ledt = new BLineEdit;
    QString s = ".{" + QString::number(required ? 1 : 0) + ","
            + ((maximimTextLength > 0) ? QString::number(maximimTextLength) : QString()) + "}";
    ledt->setValidator(new QRegExpValidator(QRegExp(s), this));
    ledt->checkValidity();
    connect(ledt, SIGNAL(textChanged(QString)), this, SLOT(checkInputs()));
    BInputField *input = new BInputField;
    input->setValid(ledt->hasAcceptableInput());
    connect(ledt, SIGNAL(inputValidityChanged(bool)), input, SLOT(setValid(bool)));
    input->addWidget(ledt);
    flt->addRow(" ", input);
}

/*============================== Public slots ==============================*/

void TAuthorInfoWidgetPrivate::checkInputs()
{
    bool bvalid = ledtName->hasAcceptableInput() && ledtOrganization->hasAcceptableInput()
            && ledtPatronymic->hasAcceptableInput() && ledtPost->hasAcceptableInput() && ledtRole->hasAcceptableInput()
            && ledtSurname->hasAcceptableInput();
    if (bvalid == valid)
        return;
    valid = bvalid;
    QMetaObject::invokeMethod(q_func(), "inputValidityChanged", Q_ARG(bool, valid));
}

void TAuthorInfoWidgetPrivate::retranslateUi()
{
    BGuiTools::labelForField<QLabel>(ledtName->parentWidget())->setText(tr("Name:", "lbl text"));
    BGuiTools::labelForField<QLabel>(ledtPatronymic->parentWidget())->setText(tr("Patronymic:", "lbl text"));
    BGuiTools::labelForField<QLabel>(ledtSurname->parentWidget())->setText(tr("Surname:", "lbl text"));
    BGuiTools::labelForField<QLabel>(ledtOrganization->parentWidget())->setText(tr("Organization:", "lbl text"));
    BGuiTools::labelForField<QLabel>(ledtPost->parentWidget())->setText(tr("Post:", "lbl text"));
    BGuiTools::labelForField<QLabel>(ledtRole->parentWidget())->setText(tr("Role:", "lbl text"));
}

/*============================================================================
================================ TAuthorInfoWidget ===========================
============================================================================*/

/*============================== Public constructors =======================*/

TAuthorInfoWidget::TAuthorInfoWidget(QWidget *parent) :
    QWidget(parent), BBaseObject(*new TAuthorInfoWidgetPrivate(this))
{
    d_func()->init();
}

TAuthorInfoWidget::~TAuthorInfoWidget()
{
    //
}

/*============================== Protected constructors ====================*/

TAuthorInfoWidget::TAuthorInfoWidget(TAuthorInfoWidgetPrivate &d, QWidget *parent) :
    QWidget(parent), BBaseObject(d)
{
    d_func()->init();
}

/*============================== Public methods ============================*/

bool TAuthorInfoWidget::hasValidInput() const
{
    return d_func()->valid;
}

TAuthorInfo TAuthorInfoWidget::info() const
{
    const B_D(TAuthorInfoWidget);
    TAuthorInfo info;
    info.setName(d->ledtName->text());
    info.setOrganization(d->ledtOrganization->text());
    info.setPatronymic(d->ledtPatronymic->text());
    info.setPost(d->ledtPost->text());
    info.setRole(d->ledtRole->text());
    info.setSurname(d->ledtSurname->text());
    return info;
}

void TAuthorInfoWidget::setInfo(const TAuthorInfo &info)
{
    B_D(TAuthorInfoWidget);
    d->ledtName->setText(info.name());
    d->ledtOrganization->setText(info.organization());
    d->ledtPatronymic->setText(info.patronymic());
    d->ledtPost->setText(info.post());
    d->ledtRole->setText(info.role());
    d->ledtSurname->setText(info.surname());
}
