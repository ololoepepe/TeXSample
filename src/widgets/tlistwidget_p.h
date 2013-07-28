#ifndef TLISTWIDGET_P_H
#define TLISTWIDGET_P_H

class QListWidget;
class QListWidgetItem;
class QToolButton;
class QSignalMapper;

#include "tlistwidget.h"

#include <BeQtGlobal>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>
#include <QString>

/*============================================================================
================================ TListWidgetPrivate ==========================
============================================================================*/

class TListWidgetPrivate : public BBasePrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TListWidget)
public:
    explicit TListWidgetPrivate(TListWidget *q);
    ~TListWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void addItem(const QString &text = QString());
    void removeSelectedItem();
    void clearList();
    void moveItemUp();
    void moveItemDown();
    void lstwgtCurrentItemChanged(QListWidgetItem *current);
public:
    bool readOnly;
    int maxCount;
    QSignalMapper *mpr;
    QListWidget *lstwgt;
    QToolButton *tbtnAdd;
    QToolButton *tbtnRemove;
    QToolButton *tbtnClear;
    QToolButton *tbtnUp;
    QToolButton *tbtnDown;
private:
    Q_DISABLE_COPY(TListWidgetPrivate)
};

#endif // TLISTWIDGET_P_H

