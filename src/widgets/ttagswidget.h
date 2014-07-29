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

#ifndef TTAGSWIDGET_H
#define TTAGSWIDGET_H

class TTagsWidgetPrivate;

class QStringList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TTagsWidget =================================
============================================================================*/

class T_WIDGETS_EXPORT TTagsWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TTagsWidget)
public:
    explicit TTagsWidget(QWidget *parent = 0);
    ~TTagsWidget();
protected:
    explicit TTagsWidget(TTagsWidgetPrivate &d, QWidget *parent = 0);
public:
    QStringList availableTags() const;
    bool isReadOnly() const;
    void setAvailableTags(const QStringList &list);
    void setReadOnly(bool ro);
    void setTags(const QStringList &list);
    QStringList tags() const;
private:
    Q_DISABLE_COPY(TTagsWidget)
};

#endif // TTAGSWIDGET_H

