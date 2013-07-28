#ifndef TUSERWIDGET_H
#define TUSERWIDGET_H

class TUserWidgetPrivate;
class TUserInfo;
class TServiceList;

class BPassword;

class QByteArray;
class QStringList;

#include <TeXSampleCore/TeXSampleGlobal>
#include <TeXSampleCore/TService>

#include <BBase>
#include <BeQtGlobal>

#include <QWidget>

/*============================================================================
================================ TUserWidget =================================
============================================================================*/

class T_WIDGETS_EXPORT TUserWidget : public QWidget, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TUserWidget)
public:
    enum Mode
    {
        AddMode,
        RegisterMode,
        EditMode,
        UpdateMode,
        ShowMode
    };
public:
    explicit TUserWidget(Mode m, QWidget *parent = 0);
    ~TUserWidget();
public:
    void setAvailableServices(const TServiceList &list);
    void setInfo(const TUserInfo &info);
    void setPassword(const BPassword &pwd);
    void setClabGroupsVisible(bool b);
    void setAvailableClabGroups(const QStringList &list);
    void setClabGroups(const QStringList &list);
    void restorePasswordWidgetState(const QByteArray &state);
    void restoreState(const QByteArray &state);
    Mode mode() const;
    TServiceList availableServices() const;
    TUserInfo info() const;
    BPassword password() const;
    bool clabGroupsVisible() const;
    QStringList availableClabGroups() const;
    QStringList clabGroups() const;
    QByteArray savePasswordWidgetState() const;
    QByteArray saveState() const;
    bool isValid() const;
Q_SIGNALS:
    void validityChanged(bool valid);
private:
    Q_DISABLE_COPY(TUserWidget)
};

#endif // TUSERWIDGET_H
