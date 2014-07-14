#ifndef TRECOVERYWIDGET_H
#define TRECOVERYWIDGET_H

class TRecoveryWidgetPrivate;

class TRecoverAccountRequestData;
class TReply;
class TRequestRecoveryCodeRequestData;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TRecoveryWidget =============================
============================================================================*/

class T_WIDGETS_EXPORT TRecoveryWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TRecoveryWidget)
public:
    typedef TReply (*RecoverAccountFunction)(const TRecoverAccountRequestData &data, QWidget *parent);
    typedef TReply (*RequestRecoveryCodeFunction)(const TRequestRecoveryCodeRequestData &data, QWidget *parent);
public:
    explicit TRecoveryWidget(RequestRecoveryCodeFunction requestRecoveryCodeFunction,
                             RecoverAccountFunction recoverAccountFunction, QWidget *parent = 0);
    ~TRecoveryWidget();
private:
    Q_DISABLE_COPY(TRecoveryWidget)
};

#endif // TRECOVERYWIDGET_H
