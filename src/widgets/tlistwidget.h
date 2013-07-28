#ifndef TLISTWIDGET_H
#define TLISTWIDGET_H

class TListWidgetPrivate;

class QStringList;

#include <BeQtGlobal>
#include <BBase>

#include <QWidget>

/*============================================================================
================================ TListWidget =================================
============================================================================*/

class TListWidget : public QWidget, public BBase
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TListWidget)
public:
    explicit TListWidget(QWidget *parent = 0);
    ~TListWidget();
protected:
    explicit TListWidget(TListWidgetPrivate &d, QWidget *parent = 0);
public:
    void setReadOnly(bool ro);
    void setButtonsVisible(bool b);
    void setAvailableItems(const QStringList &items);
    void setItems(const QStringList &list);
    void setMaxAvailableItems(int count);
    void clear();
    bool isReadOnly() const;
    bool areButtonsVisible() const;
    QStringList availableItems() const;
    QStringList items() const;
    int maxAvailableItems() const;
private:
    Q_DISABLE_COPY(TListWidget)
};

#endif // TLISTWIDGET_H

