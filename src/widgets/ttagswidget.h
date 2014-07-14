#ifndef TTAGSWIDGET_H
#define TTAGSWIDGET_H

class TTagsWidgetPrivate;

class QStringList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QWidget>

/*============================================================================
================================ TTagsWidget =================================
============================================================================*/

class T_WIDGETS_EXPORT TTagsWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TTagsWidget)
public:
    explicit TTagsWidget(QWidget *parent = 0);
    ~TTagsWidget();
protected:
    explicit TTagsWidget(TTagsWidgetPrivate &d, QWidget *parent = 0);
public:
    QStringList availableTags() const;
    bool isReadOnly() const;
    void setAvailableTags(const QStringList &list);
    void setReadOnly(bool ro);
    void setTags(const QStringList &list);
    QStringList tags() const;
private:
    Q_DISABLE_COPY(TTagsWidget)
};

#endif // TTAGSWIDGET_H

