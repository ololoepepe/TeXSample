#ifndef TSERVICELIST_H
#define TSERVICELIST_H

class QStringList;

#include "tservice.h"

#include <QList>
#include <QMetaType>
#include <QString>
#include <QVariant>

/*============================================================================
================================ TServiceList ================================
============================================================================*/

class T_CORE_EXPORT TServiceList : public QList<TService>
{
public:
    static TServiceList allServices(bool includeNoService = false);
public:
    QString toString(const QString &separator = ", ") const;
    QStringList toStringList() const;
    QStringList toStringListNoTr() const;
    QString toStringNoTr(const QString &separator = ", ") const;
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TServiceList)

#endif // TSERVICELIST_H
