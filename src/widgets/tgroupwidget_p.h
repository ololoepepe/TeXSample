#ifndef IGROUPWIDGET_H
#define IGROUPWIDGET_H

class TGroupModel;

class BPasswordWidget;

class QAction;
class QItemSelection;
class QModelIndex;
class QTableView;

#include "tgroupwidget.h"

#include <BeQtCore/private/bbaseobject_p.h>

/*============================================================================
================================ TGroupWidgetPrivate =========================
============================================================================*/

class T_WIDGETS_EXPORT TGroupWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TGroupWidget)
public:
    typedef TGroupWidget::AddGroupFunction AddGroupFunction;
    typedef TGroupWidget::DeleteGroupFunction DeleteGroupFunction;
    typedef TGroupWidget::EditGroupFunction EditGroupFunction;
public:
    TGroupModel * const Model;
public:
    QAction *actAdd;
    QAction *actDelete;
    QAction *actEdit;
    AddGroupFunction addGroupFunction;
    DeleteGroupFunction deleteGroupFunction;
    EditGroupFunction editGroupFunction;
    QTableView *view;
public:
    explicit TGroupWidgetPrivate(TGroupWidget *q, TGroupModel *model);
    ~TGroupWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void addGroup();
    void deleteGroup();
    void editGroup(const QModelIndex &index);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    Q_DISABLE_COPY(TGroupWidgetPrivate)
};

#endif // TGROUPWIDGET_H
