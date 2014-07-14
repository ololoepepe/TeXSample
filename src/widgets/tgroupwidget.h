#ifndef TGROUPWIDGET_H
#define TGROUPWIDGET_H

class TGroupWidgetPrivate;

class TAddGroupRequestData;
class TDeleteGroupRequestData;
class TEditGroupRequestData;
class TGroupModel;
class TReply;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TGroupWidget ================================
============================================================================*/

class T_WIDGETS_EXPORT TGroupWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TGroupWidget)
public:
    typedef TReply (*AddGroupFunction)(const TAddGroupRequestData &data, QWidget *parent);
    typedef TReply (*DeleteGroupFunction)(const TDeleteGroupRequestData &data, QWidget *parent);
    typedef TReply (*EditGroupFunction)(const TEditGroupRequestData &data, QWidget *parent);
public:
    explicit TGroupWidget(TGroupModel *model, QWidget *parent = 0);
    ~TGroupWidget();
public:
    AddGroupFunction addGroupFunction() const;
    DeleteGroupFunction deleteGroupFunction() const;
    EditGroupFunction editGroupFunction() const;
    void setAddGroupFunction(AddGroupFunction addGroupFunction);
    void setDeleteGroupFunction(DeleteGroupFunction deleteGroupFunction);
    void setEditGroupFunction(EditGroupFunction editGroupFunction);
private:
    Q_DISABLE_COPY(TGroupWidget)
};

#endif // TGROUPWIDGET_H
