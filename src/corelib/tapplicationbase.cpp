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

#include "tapplicationbase.h"

#include "tglobal.h"

/*============================================================================
================================ TCoreApplication ============================
============================================================================*/

/*============================== Public constructors =======================*/

TApplicationBase::TApplicationBase()
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_INIT_RESOURCE(texsample_translations);
#endif
    tRegister();
}

TApplicationBase::~TApplicationBase()
{
#if defined(TSMP_BUILTIN_RESOURCES)
    Q_CLEANUP_RESOURCE(texsample_translations);
#endif
}
