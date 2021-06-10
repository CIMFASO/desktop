#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPersistentModelIndex>
#include <QTableView>
#include <QPushButton>
#include <QDebug>
#include "customwidget.h"

class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomDelegate(QObject *parent = nullptr,QList<int> buttonsToHide = {1,2,3,4,5,6});
    ~CustomDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void setCustomColumn(int value);
    void hideToolButton(QToolButton *btn);
    void hideToolButton(const QString &objName);
    void hideButtons(CustomWidget *widget) const;

public:
    QToolButton *getBtn1(){return widget->getBtn1();};
    QToolButton *getBtn2(){return widget->getBtn2();};
    QToolButton *getBtn3(){return widget->getBtn3();};
    QToolButton *getBtn4(){return widget->getBtn4();};
    QToolButton *getBtn5(){return widget->getBtn5();};
    QToolButton *getBtn6(){return widget->getBtn6();};

    QToolButton *getDelBtn(){return widget->getDelButton();};
    QToolButton *getUpdBtn(){return widget->getUpdButton();};

    bool isUpdBtnVisible() const;
    void setUpdBtnVisible(bool value);

    bool isDelBtnVisible() const;
    void setDelBtnVisible(bool value);

    void setBtn1Text(const QString &value);
    void setBtn2Text(const QString &value);
    void setBtn3Text(const QString &value);
    void setBtn4Text(const QString &value);
    void setBtn5Text(const QString &value);
    void setBtn6Text(const QString &value);

    void hideToolButton(bool value,int num);

    QList<int> &getButtonsTohide();

    void setBtn1ToolTip(const QString &value);

    void setBtn2ToolTip(const QString &value);

    void setBtn3ToolTip(const QString &value);

    void setBtn4ToolTip(const QString &value);

    void setBtn5ToolTip(const QString &value);

    void setBtn6ToolTip(const QString &value);

public slots:
    void cellEntered(const QModelIndex &index);
    void slotUpdClick(){emit updButtonClicked(currentEditedCellIndex);}
    void slotDelClick(){emit delButtonClicked(currentEditedCellIndex);}
    void slotBtn1Click(){emit btn1Clicked(currentEditedCellIndex);}
    void slotBtn2Click(){emit btn2Clicked(currentEditedCellIndex);}
    void slotBtn3Click(){emit btn3Clicked(currentEditedCellIndex);}
    void slotBtn4Click(){emit btn4Clicked(currentEditedCellIndex);}
    void slotBtn5Click(){emit btn5Clicked(currentEditedCellIndex);}
    void slotBtn6Click(){emit btn6Clicked(currentEditedCellIndex);}
signals:
    void updButtonClicked(const QModelIndex &index);
    void delButtonClicked(const QModelIndex &index);
    void btn1Clicked(const QModelIndex &index);
    void btn2Clicked(const QModelIndex &index);
    void btn3Clicked(const QModelIndex &index);
    void btn4Clicked(const QModelIndex &index);
    void btn5Clicked(const QModelIndex &index);
    void btn6Clicked(const QModelIndex &index);
private:
    QTableView *view;
    QList<int> buttons;
    int customColumn;
    CustomWidget *widget;
    bool isOneCellInEditMode;
    bool updBtnVisible,delBtnVisible;
    QString btn1Text,btn2Text,btn3Text,btn4Text,btn5Text,btn6Text;
    QString btn1ToolTip,btn2ToolTip,btn3ToolTip,btn4ToolTip,btn5ToolTip,btn6ToolTip;
    QPersistentModelIndex currentEditedCellIndex;
};

#endif // CUSTOMDELEGATE_H
