#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QHBoxLayout>
#include <QToolButton>
#include <QDebug>
#include <QWidget>

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = nullptr);

    void addToolButton(QToolButton *btn);
    void hideToolButton(QToolButton *btn);
    void hideToolButton(const QString &objName);

    QToolButton *getDelButton();
    void setDelButton(QToolButton *value);

    QToolButton *getUpdButton();
    void setUpdButton(QToolButton *value);

    QToolButton *getBtn1() const;
    void setBtn1(QToolButton *value);

    QToolButton *getBtn2() const;
    void setBtn2(QToolButton *value);

    QToolButton *getBtn3() const;
    void setBtn3(QToolButton *value);

    QToolButton *getBtn4() const;
    void setBtn4(QToolButton *value);

    bool getUpdBtnVisible() const;
    void setUpdBtnVisible(bool value);

    bool getDelBtnVisible() const;
    void setDelBtnVisible(bool value);

    QToolButton *getBtn5() const;
    void setBtn5(QToolButton *value);

    QToolButton *getBtn6() const;
    void setBtn6(QToolButton *value);

public slots:
    void slotUpdClick(){emit updButtonClicked();}
    void slotDelClick(){emit delButtonClicked();}
    void slotBtn1Click(){emit btn1Clicked();}
    void slotBtn2Click(){emit btn2Clicked();}
    void slotBtn3Click(){emit btn3Clicked();}
    void slotBtn4Click(){emit btn4Clicked();}
    void slotBtn5Click(){emit btn5Clicked();}
    void slotBtn6Click(){emit btn6Clicked();}
signals:
    void delButtonClicked();
    void updButtonClicked();
    void btn1Clicked();
    void btn2Clicked();
    void btn3Clicked();
    void btn4Clicked();
    void btn5Clicked();
    void btn6Clicked();
private:
    QToolButton *delButton;
    QToolButton *updButton;
    QToolButton *btn1,*btn2,
                *btn3,*btn4,
                *btn5,*btn6;
    QHBoxLayout *hLayout;
    bool updBtnVisible,delBtnVisible;
};

#endif // CUSTOMWIDGET_H
