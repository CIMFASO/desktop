#ifndef CUSTOMCHECKBOXDELEGATE_H
#define CUSTOMCHECKBOXDELEGATE_H


#include <QStyledItemDelegate>
#include <QPersistentModelIndex>
#include <QTableView>
#include <QCheckBox>
#include <QDebug>

class CustomCheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomCheckBoxDelegate(QObject *parent = nullptr);
    ~CustomCheckBoxDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void setCustomColumn(int value);

public:
    QCheckBox *getCheckBox(){return widget;};
signals:
    void checkBoxClicked(const QModelIndex &index);
public slots:
    void cellEntered(const QModelIndex &index);
    void slotCheckBoxClicked(){emit checkBoxClicked(currentEditedCellIndex);}
private:
    QTableView *view;
    int customColumn;
    QCheckBox *widget;
    bool isChecked;
    bool isOneCellInEditMode;
    QPersistentModelIndex currentEditedCellIndex;
};


#endif // CUSTOMCHECKBOXDELEGATE_H
