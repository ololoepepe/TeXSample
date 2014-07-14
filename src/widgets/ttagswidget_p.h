#ifndef TTAGSWIDGET_P_H
#define TTAGSWIDGET_P_H

class QLineEdit;
class QSignalMapper;
class QString;
class QToolButton;

#include "ttagswidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

#include <QObject>

/*============================================================================
================================ TTagsWidgetPrivate ==========================
============================================================================*/

class T_WIDGETS_EXPORT TTagsWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TTagsWidget)
public:
    QToolButton *tbtn;
    QLineEdit *ledt;
    QSignalMapper *mpr;
public:
    explicit TTagsWidgetPrivate(TTagsWidget *q);
    ~TTagsWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void addTag(const QString &tag);
private:
    Q_DISABLE_COPY(TTagsWidgetPrivate)
};

#endif // TTAGSWIDGET_P_H

