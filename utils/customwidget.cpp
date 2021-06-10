#include "customwidget.h"

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    hLayout   = new QHBoxLayout();

    updButton = new QToolButton();
    delButton = new QToolButton();
    btn1 = new QToolButton();
    btn2 = new QToolButton();
    btn3 = new QToolButton();
    btn4 = new QToolButton();
    btn5 = new QToolButton();
    btn6 = new QToolButton();

    delButton->setIcon(QIcon(QPixmap(":/images/del_icon.png")));
    updButton->setIcon(QIcon(QPixmap(":/images/edit_icon.png")));

    hLayout->addWidget(btn6);
    hLayout->addWidget(btn5);
    hLayout->addWidget(btn4);
    hLayout->addWidget(btn3);
    hLayout->addWidget(btn2);
    hLayout->addWidget(btn1);
    hLayout->addWidget(updButton);
    hLayout->addWidget(delButton);

    hLayout->setSpacing(3);
    hLayout->setMargin(0);

    setLayout(hLayout);

    QObject::connect(btn1,&QToolButton::clicked,this,&CustomWidget::slotBtn1Click);
    QObject::connect(btn2,&QToolButton::clicked,this,&CustomWidget::slotBtn2Click);
    QObject::connect(btn3,&QToolButton::clicked,this,&CustomWidget::slotBtn3Click);
    QObject::connect(btn4,&QToolButton::clicked,this,&CustomWidget::slotBtn4Click);
    QObject::connect(btn5,&QToolButton::clicked,this,&CustomWidget::slotBtn5Click);
    QObject::connect(btn6,&QToolButton::clicked,this,&CustomWidget::slotBtn6Click);
    QObject::connect(updButton,&QToolButton::clicked,this,&CustomWidget::slotUpdClick);
    QObject::connect(delButton,&QToolButton::clicked,this,&CustomWidget::slotDelClick);
}

void CustomWidget::addToolButton(QToolButton *btn)
{
    hLayout->addWidget(btn);
}

void CustomWidget::hideToolButton(QToolButton *btn)
{
    btn->setVisible(false);
}

void CustomWidget::hideToolButton(const QString &objName)
{
    for (int i = 0; i < hLayout->children().count(); ++i) {
        QWidget *w = hLayout->itemAt(i)->widget();
        if(w->objectName() == objName){
            w->setHidden(true);
            break;
        }
    }
}

QToolButton *CustomWidget::getDelButton()
{
    return delButton;
}

void CustomWidget::setDelButton(QToolButton *value)
{
    delButton = value;
}

QToolButton *CustomWidget::getUpdButton()
{
    return updButton;
}

void CustomWidget::setUpdButton(QToolButton *value)
{
    updButton = value;
}

QToolButton *CustomWidget::getBtn1() const
{
    return btn1;
}

void CustomWidget::setBtn1(QToolButton *value)
{
    btn1 = value;
}

QToolButton *CustomWidget::getBtn2() const
{
    return btn2;
}

void CustomWidget::setBtn2(QToolButton *value)
{
    btn2 = value;
}

QToolButton *CustomWidget::getBtn3() const
{
    return btn3;
}

void CustomWidget::setBtn3(QToolButton *value)
{
    btn3 = value;
}

QToolButton *CustomWidget::getBtn4() const
{
    return btn4;
}

void CustomWidget::setBtn4(QToolButton *value)
{
    btn4 = value;
}

bool CustomWidget::getUpdBtnVisible() const
{
    return updBtnVisible;
}

void CustomWidget::setUpdBtnVisible(bool value)
{
    updBtnVisible = value;
}

bool CustomWidget::getDelBtnVisible() const
{
    return delBtnVisible;
}

void CustomWidget::setDelBtnVisible(bool value)
{
    delBtnVisible = value;
}

QToolButton *CustomWidget::getBtn5() const
{
    return btn5;
}

void CustomWidget::setBtn5(QToolButton *value)
{
    btn5 = value;
}

QToolButton *CustomWidget::getBtn6() const
{
    return btn6;
}

void CustomWidget::setBtn6(QToolButton *value)
{
    btn6 = value;
}
