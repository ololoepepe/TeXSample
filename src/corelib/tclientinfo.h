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

#ifndef TCLIENTINFO_H
#define TCLIENTINFO_H

class TClientInfoPrivate;

class BVersion;

class QDataStream;
class QDebug;
class QVariant;

#include "tnamespace.h"

#include <BBase>
#include <BeQt>

#include <QMetaType>
#include <QString>

/*============================================================================
================================ TClientInfo =================================
============================================================================*/

class T_CORE_EXPORT TClientInfo : public BBase
{
    B_DECLARE_PRIVATE(TClientInfo)
public:
    explicit TClientInfo();
    TClientInfo(const TClientInfo &other);
    ~TClientInfo();
public:
    static TClientInfo create();
public:
    Texsample::ClientType applicationType() const;          //%n
    BVersion applicationVersion() const;                    //%v
    BVersion beqtVersion() const;                           //%b
    bool isPortable() const;                                //%p
    bool isValid() const;
    QString os() const;                                     //%o
    BeQt::OSType osType() const;
    BeQt::ProcessorArchitecture processorArchitecture() const;
    QString processorArchitectureString() const;            //%a
    BVersion qtVersion() const;                             //%q
    BVersion texsampleVersion() const;                      //%t
    QString toString(const QString &format = "%n v%v (%p)\nTeXSample v%t; BeQt v%b; Qt v%q\nOS: %o; Arch: %a") const;
public:
    TClientInfo &operator =(const TClientInfo &other);
    bool operator ==(const TClientInfo &other) const;
    operator QVariant() const;
public:
    friend QDataStream &operator <<(QDataStream &stream, const TClientInfo &info);
    friend QDataStream &operator >>(QDataStream &stream, TClientInfo &info);
    friend QDebug operator <<(QDebug dbg, const TClientInfo &info);
};

Q_DECLARE_METATYPE(TClientInfo)

#endif // TCLIENTINFO_H
