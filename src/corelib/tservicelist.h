#ifndef TSERVICELIST_H
#define TSERVICELIST_H

class QStringList;

#include "tservice.h"

#include <QList>
#include <QMetaType>
#include <QVariant>
#include <QString>

/*============================================================================
================================ TServiceList ================================
============================================================================*/

class T_CORE_EXPORT TServiceList : public QList<TService>
{
public:
    static TServiceList serviceListFromIntList(const QList<int> &list);
    static TServiceList allServices(bool includeNoService = false);
public:
    QStringList toStringList() const;
    QStringList toStringListNoTr() const;
    QString toString(const QString &separator = ", ") const;
    QString toStringNoTr(const QString &separator = ", ") const;
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TServiceList)

#endif // TSERVICELIST_H
