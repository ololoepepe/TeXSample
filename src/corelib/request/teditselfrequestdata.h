/****************************************************************************
**
** Copyright (C) 2013-2014 Andrey Bogdanov
**
** This file is part of the TeXSampleCore module of the TeXSample library.
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

#ifndef TEDITSELFREQUESTDATA_H
#define TEDITSELFREQUESTDATA_H

class TEditSelfRequestDataPrivate;

class QDataStream;
class QDebug;
class QImage;
class QString;
class QVariant;

#include "tglobal.h"

#include <BBase>

#include <QMetaType>

/*============================================================================
================================ TEditSelfRequestData ========================
============================================================================*/

class T_CORE_EXPORT TEditSelfRequestData : public BBase
{
    B_DECLARE_PRIVATE(TEditSelfRequestData)
public:
    explicit TEditSelfRequestData();
    TEditSelfRequestData(const TEditSelfRequestData &other);
    ~TEditSelfRequestData();
public:
    QImage avatar() const;
    void clear();
    bool editAvatar() const;
    QString name() const;
    QString patronymic() const;
    bool isValid() const;
    void setAvatar(const QImage &avatar);
    void setEditAvatar(bool edit);
    void setName(const QString &name);
    void setPatronymic(const QString &patronymic);
    void setSurname(const QString &surname);
    QString surname() const;
public:
    TEditSelfRequestData &operator =(const TEditSelfRequestData &other);
    bool operator ==(const TEditSelfRequestData &other) const;
    bool operator !=(const TEditSelfRequestData &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TEditSelfRequestData &data);
    friend QDataStream &operator >>(QDataStream &stream, TEditSelfRequestData &data);
    friend QDebug operator <<(QDebug dbg, const TEditSelfRequestData &data);
};

Q_DECLARE_METATYPE(TEditSelfRequestData)

#endif // TEDITSELFREQUESTDATA_H
