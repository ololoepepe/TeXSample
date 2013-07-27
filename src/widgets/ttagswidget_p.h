#ifndef TTAGSWIDGET_P_H
#define TTAGSWIDGET_P_H

class QLineEdit;
class QToolButton;
class QString;
class QSignalMapper;

#include "ttagswidget.h"

#include <BeQtGlobal>
#include <BeQtCore/private/bbase_p.h>

#include <QObject>

/*============================================================================
================================ TTagsWidgetPrivate ==========================
============================================================================*/

class TTagsWidgetPrivate : public BBasePrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TTagsWidget)
public:
    explicit TTagsWidgetPrivate(TTagsWidget *q);
    ~TTagsWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void addTag(const QString &tag);
public:
    QSignalMapper *mpr;
    QLineEdit *ledt;
    QToolButton *tbtn;
private:
    Q_DISABLE_COPY(TTagsWidgetPrivate)
};

#endif // TTAGSWIDGET_P_H

