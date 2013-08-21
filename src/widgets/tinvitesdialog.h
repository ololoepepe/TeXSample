#ifndef TINVITESDIALOG_H
#define TINVITESDIALOG_H

class TInvitesDialogPrivate;
class TOperationResult;
class TInviteInfoList;
class TService;
class TServiceList;

class QDateTime;
class QWidget;
class QStringList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BDialog>

/*============================================================================
================================ TInvitesDialog ==============================
============================================================================*/

class T_WIDGETS_EXPORT TInvitesDialog : public BDialog
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TInvitesDialog)
public:
    typedef bool (*TestServiceFunction)(const TService &);
    typedef TOperationResult (*GetInvitesFunction)(TInviteInfoList &, QWidget *parent);
    typedef TOperationResult (*GenerateInvitesFunction)(TInviteInfoList &, const QDateTime &expirationDT, quint8 count,
                                                        const TServiceList &services, QWidget *parent);
    typedef TOperationResult (*GenerateInvitesClabFunction)(TInviteInfoList &, const QDateTime &expirationDT,
                                                            quint8 count, const TServiceList &services,
                                                            const QStringList &clabGroups, QWidget *parent);
public:
    explicit TInvitesDialog(TestServiceFunction testf, GetInvitesFunction getf, GenerateInvitesFunction genf,
                            QWidget *parent = 0);
    explicit TInvitesDialog(TestServiceFunction testf, GetInvitesFunction getf, GenerateInvitesClabFunction genf,
                            QWidget *parent = 0);
    ~TInvitesDialog();
public:
    void setClabEnabled(bool b);
    void setAvailableClabGroups(const QStringList &list);
    bool isClabEnabled() const;
    QStringList availableClabGroups() const;
private:
    Q_DISABLE_COPY(TInvitesDialog)
};

#endif // TINVITESDIALOG_H
