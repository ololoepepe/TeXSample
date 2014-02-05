#ifndef TUSERWIDGET_P_H
#define TUSERWIDGET_P_H

class TListWidget;

class BPasswordWidget;
class BInputField;
class BPasswordGroup;
class BEditGroup;

class QLineEdit;
class QComboBox;
class QToolButton;
class QCheckBox;
class QGroupBox;

#include "tuserwidget.h"

#include <TeXSampleCore/TeXSampleGlobal>
#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>

#include <BeQtGlobal>
#include <BeQtCore/private/bbase_p.h>

#include <BPassword>

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QMap>
#include <QSet>

/*============================================================================
================================ TUserWidgetPrivate ==========================
============================================================================*/

class T_WIDGETS_EXPORT TUserWidgetPrivate : public BBasePrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TUserWidget)
public:
    explicit TUserWidgetPrivate(TUserWidget *q, TUserWidget::Mode m, TUserWidget::CheckEmailFunction chkmf = 0,
                                TUserWidget::CheckLoginFunction chklf = 0);
    ~TUserWidgetPrivate();
public:
    void init();
private Q_SLOTS:
    void resetAvatar(const QByteArray &data = QByteArray());
    void checkInputs();
    void tbtnAvatarClicked();
    void checkEmail();
    void checkLogin();
public:
    const TUserWidget::Mode Mode;
    const TUserWidget::CheckEmailFunction CheckEmailFunction;
    const TUserWidget::CheckLoginFunction CheckLoginFunction;
public:
    bool valid;
    TServiceList services;
    quint64 id;
    QString avatarFileName;
    QByteArray avatar;
    QLineEdit *ledtInvite;
    BInputField *inputInvite;
    BEditGroup *edtgrpEmail;
    QLineEdit *ledtEmail;
    QToolButton *tbtnCheckEmail;
    BInputField *inputEmail;
    QLineEdit *ledtEmail2;
    BInputField *inputEmail2;
    QLineEdit *ledtLogin;
    QToolButton *tbtnCheckLogin;
    BInputField *inputLogin;
    BPasswordGroup *pwdgrp;
    BPasswordWidget *pwdwgt1;
    BInputField *inputPwd1;
    BPasswordWidget *pwdwgt2;
    BInputField *inputPwd2;
    QComboBox *cmboxAccessLevel;
    QLineEdit *ledtRealName;
    QToolButton *tbtnAvatar;
    QToolButton *tbtnClearAvatar;
    QMap<TService, QCheckBox *> cboxMap;
    QGroupBox *gboxClab;
    TListWidget *lstwgtClab;
    QSet<QString> occupiedEmails;
    QSet<QString> occupiedLogins;
private:
    Q_DISABLE_COPY(TUserWidgetPrivate)
};

#endif // TUSERWIDGET_P_H
