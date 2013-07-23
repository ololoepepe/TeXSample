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

class TSMP_EXPORT TServiceList : public QList<TService>
{
public:
    static TServiceList serviceListFromIntList(const QList<int> &list);
    static TServiceList allServices(bool includeNoService = false);
    static QStringList serviceListToStringList(const TServiceList &list);
    static QStringList serviceListToStringListNoTr(const TServiceList &list);
    static QString serviceListToString(const TServiceList &list, const QString &separator = ", ");
    static QString serviceListToStringNoTr(const TServiceList &list, const QString &separator = ", ");
public:
    operator QVariant() const;
};

Q_DECLARE_METATYPE(TServiceList)

#endif // TSERVICELIST_H
