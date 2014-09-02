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

#ifndef TINVITEINFOWIDGET_H
#define TINVITEINFOWIDGET_H

class TInviteInfoWidgetPrivate;

class TGroupInfoList;
class TIdList;
class TInviteInfo;
class TServiceList;

class QDateTime;

#include <TeXSampleCore/TAccessLevel>

#include <BBaseObject>

#include <QList>
#include <QWidget>

/*============================================================================
================================ TInviteInfoWidget ===========================
============================================================================*/

class T_WIDGETS_EXPORT TInviteInfoWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TInviteInfoWidget)
public:
    explicit TInviteInfoWidget(QWidget *parent = 0);
    ~TInviteInfoWidget();
protected:
    explicit TInviteInfoWidget(TInviteInfoWidgetPrivate &d, QWidget *parent = 0);
public:
    TAccessLevel accessLevel() const;
    QList<TAccessLevel> availableAccessLevels() const;
    TGroupInfoList availableGroups() const;
    TServiceList availableServices() const;
    quint16 count() const;
    QDateTime expirationDateTime() const;
    TGroupInfoList groups() const;
    TIdList groupIds() const;
    bool isReadOnly() const;
    quint16 maxInviteCount() const;
    TServiceList services() const;
    void setAvailableAccessLevels(const QList<TAccessLevel> &list);
    void setAvailableGroups(const TGroupInfoList &list);
    void setAvailableServices(const TServiceList &list);
    void setExpirationDateTime(const QDateTime &dt);
    void setGroups(const TGroupInfoList &list);
    void setGroups(const TIdList &list);
    void setInfo(const TInviteInfo &info);
    void setMaxInviteCount(quint16 count);
    void setReadOnly(bool ro);
    void setServices(const TServiceList &list);
private:
    Q_DISABLE_COPY(TInviteInfoWidget)
};

#endif // TINVITEINFOWIDGET_H

