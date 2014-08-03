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

#ifndef TUSERINFOWIDGET_H
#define TUSERINFOWIDGET_H

class TUserInfoWidgetPrivate;

class TNetworkClient;
class TUserModel;

class QVariant;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TUserInfoWidget =============================
============================================================================*/

class T_NETWORKWIDGETS_EXPORT TUserInfoWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TUserInfoWidget)
public:
    enum Mode
    {
        AddMode = 1,
        EditMode,
        EditSelfMode,
        RegisterMode,
        ShowMode
    };
public:
    explicit TUserInfoWidget(Mode mode, QWidget *parent = 0);
    ~TUserInfoWidget();
public:
    TNetworkClient *client() const;
    QVariant createRequestData() const;
    bool hasValidInput() const;
    Mode mode() const;
    TUserModel *model() const;
    void setClient(TNetworkClient *client);
    void setUser(quint64 userId);
    void setModel(TUserModel *model);
Q_SIGNALS:
    void inputValidityChanged(bool valid);
private:
    Q_DISABLE_COPY(TUserInfoWidget)
};

#endif // TUSERINFOWIDGET_H