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

#ifndef TUSERWIDGET_H
#define TUSERWIDGET_H

class TUserWidgetPrivate;

class TNetworkClient;
class TUserModel;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TUserWidget =================================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TUserWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TUserWidget)
public:
    explicit TUserWidget(TUserModel *model, QWidget *parent = 0);
    ~TUserWidget();
public:
    TNetworkClient *client() const;
    void setClient(TNetworkClient *client);
private:
    Q_DISABLE_COPY(TUserWidget)
};

#endif // TUSERWIDGET_H
