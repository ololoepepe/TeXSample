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

#ifndef TSERVICEWIDGET_H
#define TSERVICEWIDGET_H

class TServiceWidgetPrivate;

#include <TeXSampleCore/TServiceList>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TServiceWidget ==============================
============================================================================*/

class T_WIDGETS_EXPORT TServiceWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TServiceWidget)
public:
    explicit TServiceWidget(QWidget *parent = 0);
    ~TServiceWidget();
protected:
    explicit TServiceWidget(TServiceWidgetPrivate &d, QWidget *parent = 0);
public:
    TServiceList availableServices() const;
    bool isReadOnly() const;
    TServiceList services() const;
    void setAvailableServices(const TServiceList &list);
    void setReadOnly(bool ro);
    void setServices(const TServiceList &list);
private:
    Q_DISABLE_COPY(TServiceWidget)
};

#endif // TSERVICEWIDGET_H

