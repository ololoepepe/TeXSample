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

#ifndef TINVITEWIDGET_H
#define TINVITEWIDGET_H

class TInviteWidgetPrivate;

class TAbstractCache;
class TInviteModel;
class TNetworkClient;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TInviteWidget ===============================
============================================================================*/

class T_WIDGETS_EXPORT TInviteWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TInviteWidget)
public:
    explicit TInviteWidget(TInviteModel *model, QWidget *parent = 0);
    ~TInviteWidget();
public:
    TAbstractCache *cache() const;
    TNetworkClient *client() const;
    quint16 maximumInviteCount() const;
    void setCache(TAbstractCache *cache);
    void setClient(TNetworkClient *client);
    void setMaximumInviteCount(quint16 count);
private:
    Q_DISABLE_COPY(TInviteWidget)
};

#endif // TINVITEWIDGET_H
