#ifndef TRECOVERYDIALOG_P_H
#define TRECOVERYDIALOG_P_H

class BPasswordWidget;
class BInputField;

class QLineEdit;
class QPushButton;

#include "trecoverydialog.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtGlobal>
#include <BeQtWidgets/private/bdialog_p.h>

/*============================================================================
================================ TRecoveryDialogPrivate ======================
============================================================================*/

class T_WIDGETS_EXPORT TRecoveryDialogPrivate : public BDialogPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TRecoveryDialog)
public:
    typedef TRecoveryDialog::GetRecoveryCodeFunction GetRecoveryCodeFunction;
    typedef TRecoveryDialog::RecoverAccountFunction RecoverAccountFunction;
public:
    explicit TRecoveryDialogPrivate(TRecoveryDialog *q, GetRecoveryCodeFunction grcf, RecoverAccountFunction raf);
    ~TRecoveryDialogPrivate();
public:
    void init();
public Q_SLOTS:
    void checkInputs();
    void getCode();
    void recoverAccount();
public:
    const GetRecoveryCodeFunction GetFunction;
    const RecoverAccountFunction RecoverFunction;
public:
    QLineEdit *mledtEmail;
    BInputField *minputEmail;
    QPushButton *mbtnGet;
    QLineEdit *mledtCode;
    BInputField *minputCode;
    BPasswordWidget *mpwdwgt1;
    BInputField *minputPwd1;
    BPasswordWidget *mpwdwgt2;
    BInputField *minputPwd2;
    QPushButton *mbtnRecover;
};

#endif // TRECOVERYDIALOG_P_H
