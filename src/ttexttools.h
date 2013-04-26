#ifndef TTEXTTOOLS_H
#define TTEXTTOOLS_H

#include "tglobal.h"

#include <QString>
#include <QRegExp>
#include <QStringList>
#include <QList>

namespace TTextTools
{

class TSMP_EXPORT SearchResult
{
public:
    explicit SearchResult(const QString *const t, int p, int l);
    SearchResult(const SearchResult &other);
public:
    QString text() const;
    int position() const;
    int length() const;
public:
    SearchResult &operator =(const SearchResult &other);
    bool operator ==(const SearchResult &other) const;
private:
    const QString *txt;
    int pos;
    int len;
};

typedef QList<SearchResult> SearchResults;

TSMP_EXPORT QStringList removeDuplicates(const QStringList &list, Qt::CaseSensitivity cs = Qt::CaseSensitive, int *count  = 0);
TSMP_EXPORT int removeDuplicates(QStringList *list, Qt::CaseSensitivity cs = Qt::CaseSensitive);
TSMP_EXPORT QStringList sortComprising(const QStringList &list, Qt::CaseSensitivity cs = Qt::CaseSensitive);
TSMP_EXPORT void sortComprising(QStringList *list, Qt::CaseSensitivity cs = Qt::CaseSensitive);
TSMP_EXPORT SearchResults match(const QString &text, const QRegExp &what, const QRegExp &prefixedBy = QRegExp(),
                                const QRegExp &postfixedBy = QRegExp());

}

#endif // TTEXTTOOLS_H
