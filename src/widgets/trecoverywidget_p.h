#ifndef TRECOVERYWIDGET_P_H
#define TRECOVERYWIDGET_P_H

class BInputField;
class BPasswordGroup;
class BPasswordWidget;

class QLineEdit;
class QPushButton;

#include "trecoverywidget.h"

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtCore/private/bbaseobject_p.h>

/*============================================================================
================================ TRecoveryWidgetPrivate ======================
============================================================================*/

class T_WIDGETS_EXPORT TRecoveryWidgetPrivate : public BBaseObjectPrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TRecoveryWidget)
public:
    typedef TRecoveryWidget::RequestRecoveryCodeFunction RequestRecoveryCodeFunction;
    typedef TRecoveryWidget::RecoverAccountFunction RecoverAccountFunction;
public:
    const RequestRecoveryCodeFunction RequestFunction;
    const RecoverAccountFunction RecoverFunction;
public:
    QPushButton *btnGet;
    QPushButton *btnRecover;
    BInputField *inputCode;
    BInputField *inputEmail;
    BInputField *inputPwd1;
    BInputField *inputPwd2;
    QLineEdit *ledtCode;
    QLineEdit *ledtEmail;
    BPasswordGroup *pwdgrp;
    BPasswordWidget *pwdwgt1;
    BPasswordWidget *pwdwgt2;
public:
    explicit TRecoveryWidgetPrivate(TRecoveryWidget *q, RequestRecoveryCodeFunction requestRecoveryCodeFunction,
                                    RecoverAccountFunction recoverAccountFunction);
    ~TRecoveryWidgetPrivate();
public:
    void init();
public Q_SLOTS:
    void checkInputs();
    void getCode();
    void recoverAccount();
};

#endif // TRECOVERYWIDGET_P_H
