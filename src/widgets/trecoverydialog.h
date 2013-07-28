#ifndef TRECOVERYDIALOG_H
#define TRECOVERYDIALOG_H

class TRecoveryDialogPrivate;
class TOperationResult;

class QWidget;
class QString;
class QByteArray;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BDialog>
#include <BeQtGlobal>

/*============================================================================
================================ TRecoveryDialog =============================
============================================================================*/

class T_WIDGETS_EXPORT TRecoveryDialog : public BDialog
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TRecoveryDialog)
public:
    typedef TOperationResult (*GetRecoveryCodeFunction)(const QString &email, QWidget *parent);
    typedef TOperationResult (*RecoverAccountFunction)(const QString &email, const QString &code,
                                                       const QByteArray &password, QWidget *parent);
public:
    explicit TRecoveryDialog(GetRecoveryCodeFunction grcf, RecoverAccountFunction raf, QWidget *parent = 0);
    ~TRecoveryDialog();
private:
    Q_DISABLE_COPY(TRecoveryDialog)
};

#endif // TRECOVERYDIALOG_H
