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

#ifndef TAUTHORINFOWIDGET_H
#define TAUTHORINFOWIDGET_H

class TAuthorInfoWidgetPrivate;

class TAuthorInfo;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TAuthorInfoWidget ===========================
============================================================================*/

class T_WIDGETS_EXPORT TAuthorInfoWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TAuthorInfoWidget)
public:
    explicit TAuthorInfoWidget(QWidget *parent = 0);
    ~TAuthorInfoWidget();
protected:
    explicit TAuthorInfoWidget(TAuthorInfoWidgetPrivate &d, QWidget *parent = 0);
public:
    bool hasValidInput() const;
    TAuthorInfo info() const;
    bool isReadOnly() const;
    void setInfo(const TAuthorInfo &info);
    void setReadOnly(bool ro);
Q_SIGNALS:
    void inputValidityChanged(bool valid);
private:
    Q_DISABLE_COPY(TAuthorInfoWidget)
};

#endif // TAUTHORINFOWIDGET_H
