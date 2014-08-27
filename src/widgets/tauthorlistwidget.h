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

#ifndef TAUTHORLISTWIDGET_H
#define TAUTHORLISTWIDGET_H

class TAuthorListWidgetPrivate;

class TAuthorInfoList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TAuthorListWidget ===========================
============================================================================*/

class T_WIDGETS_EXPORT TAuthorListWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TAuthorListWidget)
public:
    explicit TAuthorListWidget(QWidget *parent = 0);
    ~TAuthorListWidget();
protected:
    explicit TAuthorListWidget(TAuthorListWidgetPrivate &d, QWidget *parent = 0);
public:
    TAuthorInfoList availableAuthors() const;
    bool buttonsVisible() const;
    TAuthorInfoList authors() const;
    bool isReadOnly() const;
    void setAvailableAuthors(const TAuthorInfoList &list);
    void setButtonsVisible(bool b);
    void setAuthors(const TAuthorInfoList &list);
    void setReadOnly(bool ro);
private:
    Q_DISABLE_COPY(TAuthorListWidget)
};

#endif // TAUTHORLISTWIDGET_H

