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

#ifndef TINVITEWIDGET_H
#define TINVITEWIDGET_H

class TInviteWidgetPrivate;

class TAccessLevel;
class TDeleteInvitesRequestData;
class TGenerateInvitesRequestData;
class TGroupInfoList;
class TInviteModel;
class TReply;
class TServiceList;

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
    typedef TReply (*DeleteInvitesFunction)(const TDeleteInvitesRequestData &data, QWidget *parent);
    typedef TReply (*GenerateInvitesFunction)(const TGenerateInvitesRequestData &data, QWidget *parent);
public:
    explicit TInviteWidget(TInviteModel *model, const TAccessLevel &accessLevel, QWidget *parent = 0);
    ~TInviteWidget();
public:
    TGroupInfoList availableGroups() const;
    TServiceList availableServices() const;
    DeleteInvitesFunction deleteInvitesFunction() const;
    GenerateInvitesFunction generateInvitesFunction() const;
    quint16 maximumInviteCount() const;
    void setAvailableGroups(const TGroupInfoList &groups);
    void setAvailableServices(const TServiceList &services);
    void setDeleteInvitesFunction(DeleteInvitesFunction deleteInvitesFunction);
    void setGenerateInvitesFunction(GenerateInvitesFunction generateInvitesFunction);
    void setMaximumInviteCount(quint16 count);
private:
    Q_DISABLE_COPY(TInviteWidget)
};

#endif // TINVITEWIDGET_H
