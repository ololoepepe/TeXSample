/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleNetworkWidgets module
** of the TeXSample library.
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

#ifndef TCONFIRMATIONWIDGET_H
#define TCONFIRMATIONWIDGET_H

class TConfirmationWidgetPrivate;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TConfirmationWidget =========================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TConfirmationWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TConfirmationWidget)
public:
    explicit TConfirmationWidget(QWidget *parent = 0);
    ~TConfirmationWidget();
public:
    bool hasValidInput() const;
Q_SIGNALS:
    void inputValidityChanged(bool valid);
private:
    Q_DISABLE_COPY(TConfirmationWidget)
};

#endif // TCONFIRMATIONWIDGET_H
