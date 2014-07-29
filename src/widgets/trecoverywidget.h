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

#ifndef TRECOVERYWIDGET_H
#define TRECOVERYWIDGET_H

class TRecoveryWidgetPrivate;

class TRecoverAccountRequestData;
class TReply;
class TRequestRecoveryCodeRequestData;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TRecoveryWidget =============================
============================================================================*/

class T_WIDGETS_EXPORT TRecoveryWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TRecoveryWidget)
public:
    typedef TReply (*RecoverAccountFunction)(const TRecoverAccountRequestData &data, QWidget *parent);
    typedef TReply (*RequestRecoveryCodeFunction)(const TRequestRecoveryCodeRequestData &data, QWidget *parent);
public:
    explicit TRecoveryWidget(RequestRecoveryCodeFunction requestRecoveryCodeFunction,
                             RecoverAccountFunction recoverAccountFunction, QWidget *parent = 0);
    ~TRecoveryWidget();
private:
    Q_DISABLE_COPY(TRecoveryWidget)
};

#endif // TRECOVERYWIDGET_H
