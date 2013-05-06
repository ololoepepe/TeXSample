#include "ttexttools.h"

#include <BeQtGlobal>

#include <QString>
#include <QRegExp>
#include <QStringList>
#include <QList>

#include <QDebug>

namespace TTextTools
{

/*============================================================================
================================ SearchResult ================================
============================================================================*/

/*============================== Public constructors =======================*/

SearchResult::SearchResult(const QString *const t, int p, int l)
{
    txt = t;
    pos = p;
    len = l;
}

SearchResult::SearchResult(const SearchResult &other)
{
    *this = other;
}

/*============================== Public methods ============================*/

QString SearchResult::text() const
{
    return txt ? txt->mid(pos, len) : QString();
}

int SearchResult::position() const
{
    return pos;
}

int SearchResult::length() const
{
    return len;
}

/*============================== Public operators ==========================*/

SearchResult &SearchResult::operator =(const SearchResult &other)
{
    txt = other.txt;
    pos = other.pos;
    len = other.len;
    return *this;
}

bool SearchResult::operator ==(const SearchResult &other) const
{
    return txt == other.txt && pos == other.pos && len == other.len;
}

/*============================================================================
================================ SearchResults ===============================
============================================================================*/

/*============================== Public methods ============================*/

QStringList SearchResults::texts() const
{
    QStringList list;
    foreach (const SearchResult r, *this)
        list << r.text();
    return list;
}

/*============================== Public operators ==========================*/

SearchResults::operator QStringList() const
{
    return texts();
}

/*============================================================================
================================ Functions ===================================
============================================================================*/

QStringList removeDuplicates(const QStringList &list, Qt::CaseSensitivity cs, int *count)
{
    QStringList nlist = list;
    int c = removeDuplicates(&nlist, cs);
    return bRet(count, c, nlist);
}

int removeDuplicates(QStringList *list, Qt::CaseSensitivity cs)
{
    if (!list)
        return 0;
    int count = 0;
    foreach (int i, bRangeR(list->size() - 1, 1))
    {
        foreach (int j, bRangeR(i - 1, 0))
        {
            if (!list->at(i).compare(list->at(j), cs))
            {
                list->removeAt(i);
                ++count;
                continue;
            }
        }
    }
    return count;
}

QStringList removeAll(const QStringList &list, const QString &what, Qt::CaseSensitivity cs, int *count)
{
    QStringList nlist = list;
    int c = removeAll(&nlist, what, cs);
    return bRet(count, c, nlist);
}

int removeAll(QStringList *list, const QString &what, Qt::CaseSensitivity cs)
{
    if (!list)
        return 0;
    int count = 0;
    foreach (int i, bRangeR(list->size() - 1, 0))
    {
        if (!what.compare(list->at(i), cs))
        {
            list->removeAt(i);
            ++count;
        }
    }
    return count;
}

QStringList sortComprising(const QStringList &list, Qt::CaseSensitivity cs)
{
    QStringList nlist = list;
    sortComprising(&nlist, cs);
    return nlist;
}

void sortComprising(QStringList *list, Qt::CaseSensitivity cs)
{
    if (!list || list->size() < 2)
        return;
    QStringList nlist;
    foreach (int i, bRangeR(list->size() - 1, 0))
    {
        foreach (int j, bRangeR(list->size() - 1, 0))
        {
            if (i != j && list->at(j).contains(list->at(i), cs))
            {
                QString s = list->takeAt(i);
                bool b = false;
                foreach (int k, bRangeD(0, nlist.size() - 1))
                {
                    if (s.contains(nlist.at(k), cs))
                    {
                        if (!s.compare(nlist.at(k), cs))
                            nlist.insert(k, s);
                        else
                            nlist.prepend(s);
                        b = true;
                        break;
                    }
                }
                if (!b)
                    nlist.append(s);
                break;
            }
        }
    }
    *list += nlist;
}

SearchResults match(const QString &text, const QRegExp &what, const QRegExp &prefixedBy, const QRegExp &postfixedBy)
{
    SearchResults list;
    if (text.isEmpty() || !what.isValid())
        return list;
    QStringList sl = text.split('\n');
    int coveredLength = 0;
    foreach (int i, bRangeD(0, sl.size() - 1))
    {
        const QString &line = sl.at(i);
        int pos = what.indexIn(line);
        while (pos >= 0)
        {
            bool b = true;
            int len = what.matchedLength();
            if (!prefixedBy.isEmpty() && prefixedBy.isValid())
            {
                int prind = prefixedBy.indexIn(line.mid(0, pos));
                if (prind < 0 || prind + prefixedBy.matchedLength() != pos)
                {
                    prind = prefixedBy.indexIn(line.mid(pos, len));
                    if (prind == 0)
                    {
                        pos += prefixedBy.matchedLength();
                        len -= prefixedBy.matchedLength();
                    }
                    else
                    {
                        b = false;
                    }
                }
            }
            if (!postfixedBy.isEmpty() && postfixedBy.isValid())
            {
                int poind = postfixedBy.indexIn(line.mid(pos + len));
                if (poind != 0)
                {
                    QString s = line.mid(pos, len);
                    poind = postfixedBy.indexIn(s);
                    if (poind >= 0 && poind + postfixedBy.matchedLength() == s.length())
                        len -= postfixedBy.matchedLength();
                    else
                        b = false;
                }
            }
            if (b && line.mid(pos, len).contains(what))
                list << SearchResult(&text, coveredLength + pos, len);
            pos = what.indexIn(line, pos + (len ? len : 1));
        }
        coveredLength += line.length() + 1;
    }
    return list;
}

bool intersects(const QStringList &list1, const QStringList &list2, Qt::CaseSensitivity cs)
{
    foreach (const QString &s1, list1)
        if (list2.contains(s1, cs))
            return true;
    return false;
}

}
