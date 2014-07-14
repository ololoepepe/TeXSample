#ifndef TINVITEWIDGET_H
#define TINVITEWIDGET_H

class TInviteWidgetPrivate;

class TAccessLevel;
class TDeleteInvitesRequestData;
class TGenerateInvitesRequestData;
class TGroupInfoList;
class TInviteModel;
class TReply;
class TServiceList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TInviteWidget ===============================
============================================================================*/

class T_WIDGETS_EXPORT TInviteWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TInviteWidget)
public:
    typedef TReply (*DeleteInvitesFunction)(const TDeleteInvitesRequestData &data, QWidget *parent);
    typedef TReply (*GenerateInvitesFunction)(const TGenerateInvitesRequestData &data, QWidget *parent);
public:
    explicit TInviteWidget(TInviteModel *model, const TAccessLevel &accessLevel, QWidget *parent = 0);
    ~TInviteWidget();
public:
    TGroupInfoList availableGroups() const;
    TServiceList availableServices() const;
    DeleteInvitesFunction deleteInvitesFunction() const;
    GenerateInvitesFunction generateInvitesFunction() const;
    void setAvailableGroups(const TGroupInfoList &groups);
    void setAvailableServices(const TServiceList &services);
    void setDeleteInvitesFunction(DeleteInvitesFunction deleteInvitesFunction);
    void setGenerateInvitesFunction(GenerateInvitesFunction generateInvitesFunction);
private:
    Q_DISABLE_COPY(TInviteWidget)
};

#endif // TINVITEWIDGET_H
