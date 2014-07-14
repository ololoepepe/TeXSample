#ifndef TLISTWIDGET_P_H
#define TLISTWIDGET_P_H

class QListWidget;
class QListWidgetItem;
class QToolButton;

#include "tlistwidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>
#include <QString>
#include <QVariant>

/*============================================================================
================================ TListWidgetPrivate ==========================
============================================================================*/

class T_WIDGETS_EXPORT TListWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TListWidget)
public:
    QListWidget *lstwgt;
    int maxCount;
    bool readOnly;
    QToolButton *tbtnAdd;
    QToolButton *tbtnClear;
    QToolButton *tbtnDown;
    QToolButton *tbtnRemove;
    QToolButton *tbtnUp;
public:
    explicit TListWidgetPrivate(TListWidget *q);
    ~TListWidgetPrivate();
public:
    static bool itemsEqual(const TListWidget::Item &item1, const TListWidget::Item &item2);
public:
    void init();
public Q_SLOTS:
    void addItem(QString text = QString(), QVariant data = QVariant());
    void clearList();
    void lstwgtCurrentItemChanged(QListWidgetItem *current);
    void moveItemDown();
    void moveItemUp();
    void removeSelectedItem();
private:
    Q_DISABLE_COPY(TListWidgetPrivate)
};

#endif // TLISTWIDGET_P_H

