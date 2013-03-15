#ifndef TGLOBAL_H
#define TGLOBAL_H

#include <QtGlobal>
#include <QList>
#include <QString>

#if defined(TSMP_BUILD_LIB)
#   define TSMP_EXPORT Q_DECL_EXPORT
#else
#   define TSMP_EXPORT Q_DECL_IMPORT
#endif

TSMP_EXPORT void tRegister();
TSMP_EXPORT const char *tVersion();

#endif // TGLOBAL_H
