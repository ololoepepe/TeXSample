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

T_CORE_EXPORT void tInit();
T_CORE_EXPORT void tCleanup();
T_CORE_EXPORT const char *tVersion();

#endif // TGLOBAL_H
