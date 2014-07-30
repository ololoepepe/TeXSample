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

class TAccessLevel;
class TChangeEmailRequestData;
class TChangePasswordRequestData;
class TCheckEmailAvailabilityRequestData;
class TCheckLoginAvailabilityRequestData;
class TGetUserAvatarRequestData;
class TGroupInfoList;
class TReply;
class TServiceList;
class TUserInfo;

class QString;
class QVariant;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TUserInfoWidget =============================
============================================================================*/

class T_WIDGETS_EXPORT TUserInfoWidget : public QWidget, public BBaseObject
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
    typedef TReply (*ChangeEmailFunction)(const TChangeEmailRequestData &data, QWidget *parent);
    typedef TReply (*ChangePasswordFunction)(const TChangePasswordRequestData &data, QWidget *parent);
    typedef TReply (*CheckEmailFunction)(const TCheckEmailAvailabilityRequestData, QWidget *parent);
    typedef TReply (*CheckLoginFunction)(const TCheckLoginAvailabilityRequestData, QWidget *parent);
    typedef TReply (*GetUserAvatarFunction)(const TGetUserAvatarRequestData, QWidget *parent);
public:
    explicit TUserInfoWidget(Mode mode, const TAccessLevel &accessLevel, QWidget *parent = 0);
    explicit TUserInfoWidget(QWidget *parent = 0);
    ~TUserInfoWidget();
public:
    TGroupInfoList availableGroups() const;
    TServiceList availableServices() const;
    ChangeEmailFunction changeEmailFunction() const;
    ChangePasswordFunction changePasswordFunction() const;
    CheckEmailFunction checkEmailFunction() const;
    CheckLoginFunction checkLoginFunction() const;
    QVariant createRequestData() const;
    GetUserAvatarFunction getUserAvatarFunction() const;
    bool hasValidInput() const;
    Mode mode() const;
    void setAvailableGroups(const TGroupInfoList &groups);
    void setAvailableServices(const TServiceList &services);
    void setChangeEmailFunction(ChangeEmailFunction function);
    void setChangePasswordFunction(ChangePasswordFunction function);
    void setCheckEmailFunction(CheckEmailFunction function);
    void setCheckLoginFunction(CheckLoginFunction function);
    void setGetUserAvatarFunction(GetUserAvatarFunction function);
    void setInfo(const TUserInfo &info);
Q_SIGNALS:
    void inputValidityChanged(bool valid);
private:
    Q_DISABLE_COPY(TUserInfoWidget)
};

#endif // TUSERINFOWIDGET_H
