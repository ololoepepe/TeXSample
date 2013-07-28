#ifndef TTAGSWIDGET_H
#define TTAGSWIDGET_H

class TTagsWidgetPrivate;

class QStringList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BeQtGlobal>
#include <BBase>

#include <QWidget>

/*============================================================================
================================ TTagsWidget =================================
============================================================================*/

class T_WIDGETS_EXPORT TTagsWidget : public QWidget, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TTagsWidget)
public:
    explicit TTagsWidget(QWidget *parent = 0);
    ~TTagsWidget();
protected:
    explicit TTagsWidget(TTagsWidgetPrivate &d, QWidget *parent = 0);
public:
    void setAvailableTags(const QStringList &list);
    void setTags(const QStringList &list);
    void setReadOnly(bool ro);
    QStringList availableTags() const;
    QStringList tags() const;
    bool isReadOnly() const;
private:
    Q_DISABLE_COPY(TTagsWidget)
};

#endif // TTAGSWIDGET_H

