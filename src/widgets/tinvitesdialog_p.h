#ifndef INVITESDIALOG_H
#define INVITESDIALOG_H

class BPasswordWidget;

class QTableWidget;
class QTableWidgetItem;
class QAction;
class QToolBar;

#include "tinvitesdialog.h"

#include <TeXSampleCore/TeXSampleGlobal>
#include <TeXSampleCore/TInviteInfoList>

#include <BeQtGlobal>
#include <BeQtWidgets/private/bdialog_p.h>

#include <QStringList>

/*============================================================================
================================ TInvitesDialogPrivate =======================
============================================================================*/

class T_WIDGETS_EXPORT TInvitesDialogPrivate : public BDialogPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TInvitesDialog)
public:
    typedef TInvitesDialog::TestServiceFunction TestServiceFunction;
    typedef TInvitesDialog::GetInvitesFunction GetInvitesFunction;
    typedef TInvitesDialog::GenerateInvitesFunction GenerateInvitesFunction;
    typedef TInvitesDialog::GenerateInvitesClabFunction GenerateInvitesClabFunction;
public:
    explicit TInvitesDialogPrivate(TInvitesDialog *q, TestServiceFunction testf, GetInvitesFunction getf,
                                   GenerateInvitesFunction genf, GenerateInvitesClabFunction gencf = 0);
    ~TInvitesDialogPrivate();
public:
    void init();
public Q_SLOTS:
    void generateInvite();
    void copyInvite(QTableWidgetItem *item = 0);
    void updateInvitesList(TInviteInfoList list = TInviteInfoList());
    void tblwgtCurrentItemChanged(QTableWidgetItem *current);
public:
    const TestServiceFunction TestFunction;
    const GetInvitesFunction GetFunction;
    const GenerateInvitesFunction GenerateFunction;
    const GenerateInvitesClabFunction GenerateClabFunction;
public:
    bool clab;
    QStringList clabGroups;
    QTableWidget *tblwgt;
    QToolBar *tbar;
    QAction *actCopy;
private:
    Q_DISABLE_COPY(TInvitesDialogPrivate)
};

#endif // INVITESDIALOG_H
