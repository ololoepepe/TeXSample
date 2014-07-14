#ifndef TLISTWIDGET_H
#define TLISTWIDGET_H

class TListWidgetPrivate;

class QStringList;

#include <TeXSampleCore/TeXSampleGlobal>

#include <BBaseObject>

#include <QList>
#include <QString>
#include <QVariant>
#include <QWidget>

/*============================================================================
================================ TListWidget =================================
============================================================================*/

class T_WIDGETS_EXPORT TListWidget : public QWidget, public BBaseObject
{
    Q_OBJECT
    B_DECLARE_PRIVATE(TListWidget)
public:
    struct Item
    {
        QVariant data;
        QString text;
    };
public:
    explicit TListWidget(QWidget *parent = 0);
    ~TListWidget();
protected:
    explicit TListWidget(TListWidgetPrivate &d, QWidget *parent = 0);
public:
    int availableItemCount() const;
    QVariant availableItemData(int index) const;
    QStringList availableItems() const;
    bool buttonsVisible() const;
    void clear();
    bool isReadOnly() const;
    int itemCount() const;
    QVariant itemData(int index) const;
    QStringList items() const;
    int maxAvailableItems() const;
    void setAvailableItemData(int index, const QVariant &data);
    void setAvailableItems(QList<Item> list);
    void setAvailableItems(const QStringList &list);
    void setButtonsVisible(bool b);
    void setItemData(int index, const QVariant &data);
    void setItems(QList<Item> list);
    void setItems(const QStringList &list);
    void setMaxAvailableItems(int count);
    void setReadOnly(bool ro);
private:
    Q_DISABLE_COPY(TListWidget)
};

#endif // TLISTWIDGET_H

