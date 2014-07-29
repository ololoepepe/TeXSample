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

#ifndef TGLOBAL_H
#define TGLOBAL_H

#include <QtGlobal>

#if defined(TSMP_BUILD_CORE_LIB)
#   define T_CORE_EXPORT Q_DECL_EXPORT
#else
#   define T_CORE_EXPORT Q_DECL_IMPORT
#endif

#if defined(TSMP_BUILD_WIDGETS_LIB)
#   define T_WIDGETS_EXPORT Q_DECL_EXPORT
#else
#   define T_WIDGETS_EXPORT Q_DECL_IMPORT
#endif

T_CORE_EXPORT void tRegister();
T_CORE_EXPORT const char *tVersion();

#endif // TGLOBAL_H
