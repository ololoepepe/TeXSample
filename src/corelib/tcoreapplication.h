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

#ifndef TCOREAPPLICATION_H
#define TCOREAPPLICATION_H

#include "tglobal.h"

#include <BCoreApplication>

#include <QString>

#define tApp (static_cast<TCoreApplication *>(BApplicationBase::binstance()))
#if defined(bApp)
#   undef bApp
#endif
#define bApp (static_cast<TApplication *>(BApplicationBase::binstance()))

/*============================================================================
================================ TApplication ================================
============================================================================*/

class T_CORE_EXPORT TCoreApplication : public BCoreApplication
{
    Q_OBJECT
public:
    explicit TCoreApplication(int &argc, char **argv, const QString &applicationName = QString(),
                          const QString &organizationName = QString());
    explicit TCoreApplication(int &argc, char **argv, const InitialSettings &s);
    ~TCoreApplication();
private:
    Q_DISABLE_COPY(TCoreApplication)
};

#endif // TCOREAPPLICATION_H

