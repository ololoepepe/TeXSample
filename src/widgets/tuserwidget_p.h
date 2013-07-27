#ifndef TUSERWIDGET_P_H
#define TUSERWIDGET_P_H

class BPasswordWidget;
class BInputField;

class QLineEdit;
class QComboBox;
class QToolButton;
class QCheckBox;


#include "tuserwidget.h"

#include <TeXSampleCore/TService>
#include <TeXSampleCore/TServiceList>

#include <BeQtGlobal>
#include <BeQtCore/private/bbase_p.h>

#include <BPassword>

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QMap>

/*============================================================================
================================ TUserWidgetPrivate ==========================
============================================================================*/

class T_WIDGETS_EXPORT TUserWidgetPrivate : public BBasePrivate
{
    Q_OBJECT
    B_DECLARE_PUBLIC(TUserWidget)
public:
    explicit TUserWidgetPrivate(TUserWidget *q, TUserWidget::Mode m);
    ~TUserWidgetPrivate();
public:
    void init();
private Q_SLOTS:
    void resetAvatar(const QByteArray &data = QByteArray());
    void checkInputs();
    void tbtnAvatarClicked();
public:
    const TUserWidget::Mode Mode;
public:
    bool valid;
    TServiceList services;
    quint64 id;
    QString avatarFileName;
    QByteArray avatar;
    QLineEdit *ledtInvite;
    BInputField *inputInvite;
    QLineEdit *ledtEmail;
    BInputField *inputEmail;
    QLineEdit *ledtLogin;
    BInputField *inputLogin;
    BPasswordWidget *pwdwgt1;
    BInputField *inputPwd1;
    BPasswordWidget *pwdwgt2;
    BInputField *inputPwd2;
    QComboBox *cmboxAccessLevel;
    QLineEdit *ledtRealName;
    QToolButton *tbtnAvatar;
    QToolButton *tbtnClearAvatar;
    QMap<TService, QCheckBox *> cboxMap;
private:
    Q_DISABLE_COPY(TUserWidgetPrivate)
};

#endif // TUSERWIDGET_P_H
