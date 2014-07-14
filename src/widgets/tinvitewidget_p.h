#ifndef INVITEWIDGET_H
#define INVITEWIDGET_H

class TInviteModel;

class BPasswordWidget;

class QAction;
class QItemSelection;
class QModelIndex;
class QTableView;

#include "tinvitewidget.h"

#include <TeXSampleCore/TAccessLevel>
#include <TeXSampleCore/TGroupInfoList>
#include <TeXSampleCore/TServiceList>

#include <BeQtCore/private/bbaseobject_p.h>

/*============================================================================
================================ TInviteWidgetPrivate ========================
============================================================================*/

class T_WIDGETS_EXPORT TInviteWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TInviteWidget)
public:
    typedef TInviteWidget::DeleteInvitesFunction DeleteInvitesFunction;
    typedef TInviteWidget::GenerateInvitesFunction GenerateInvitesFunction;
public:
    const TAccessLevel AccessLevel;
    TInviteModel * const Model;
public:
    QAction *actCopy;
    QAction *actDelete;
    QAction *actGenerate;
    TServiceList availableServices;
    TGroupInfoList availableGroups;
    DeleteInvitesFunction deleteInvitesFunction;
    GenerateInvitesFunction generateInvitesFunction;
    QTableView *view;
public:
    explicit TInviteWidgetPrivate(TInviteWidget *q, TInviteModel *model, const TAccessLevel &accessLevel);
    ~TInviteWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void copyInvites();
    void deleteInvites();
    void generateInvites();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
    Q_DISABLE_COPY(TInviteWidgetPrivate)
};

#endif // TINVITEWIDGET_H
