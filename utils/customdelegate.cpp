#include "customdelegate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>

CustomDelegate::CustomDelegate(QObject *parent, QList<int> buttonsToHide) : QStyledItemDelegate(parent),customColumn(3),updBtnVisible(true),delBtnVisible(true)
{
    if(QTableView *tableView = qobject_cast<QTableView*>(parent))
    {
        view = tableView;

        widget = new CustomWidget(view);
        widget->setObjectName("btn");

        widget->getBtn1()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        widget->getBtn2()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        widget->getBtn3()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        widget->getBtn4()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        widget->getBtn5()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        widget->getBtn6()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        widget->getBtn1()->setContextMenuPolicy(Qt::CustomContextMenu);
        widget->getBtn2()->setContextMenuPolicy(Qt::CustomContextMenu);
        widget->getBtn3()->setContextMenuPolicy(Qt::CustomContextMenu);
        widget->getBtn4()->setContextMenuPolicy(Qt::CustomContextMenu);
        widget->getBtn5()->setContextMenuPolicy(Qt::CustomContextMenu);
        widget->getBtn6()->setContextMenuPolicy(Qt::CustomContextMenu);

        buttons = buttonsToHide;

        hideButtons(widget);

        widget->hide();

        view->setMouseTracking(true);

        connect(view,&QTableView::entered,this,&CustomDelegate::cellEntered);
        connect(widget,&CustomWidget::btn1Clicked,this,&CustomDelegate::slotBtn1Click);
        connect(widget,&CustomWidget::btn2Clicked,this,&CustomDelegate::slotBtn2Click);
        connect(widget,&CustomWidget::btn3Clicked,this,&CustomDelegate::slotBtn3Click);
        connect(widget,&CustomWidget::btn4Clicked,this,&CustomDelegate::slotBtn4Click);
        connect(widget,&CustomWidget::btn5Clicked,this,&CustomDelegate::slotBtn5Click);
        connect(widget,&CustomWidget::btn6Clicked,this,&CustomDelegate::slotBtn6Click);
        connect(widget,&CustomWidget::updButtonClicked,this,&CustomDelegate::slotUpdClick);
        connect(widget,&CustomWidget::delButtonClicked,this,&CustomDelegate::slotDelClick);

        isOneCellInEditMode = false;
    }
}

CustomDelegate::~CustomDelegate()
{
    delete widget;
}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == customColumn){

        widget->setGeometry(option.rect);
        widget->setObjectName("btn");

        if(option.state == QStyle::State_Selected)
        {
            painter->fillRect(option.rect,option.palette.highlight());
        }

        QPixmap map = widget->grab();
        painter->setBrush(Qt::white);
        painter->drawPixmap(option.rect.x(),option.rect.y(),map);

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget *CustomDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == customColumn)
    {
        CustomWidget *w = new CustomWidget(parent);
        w->getBtn1()->setIcon(widget->getBtn1()->icon());
        w->getBtn2()->setIcon(widget->getBtn2()->icon());
        w->getBtn3()->setIcon(widget->getBtn3()->icon());
        w->getBtn4()->setIcon(widget->getBtn4()->icon());
        w->getBtn5()->setIcon(widget->getBtn5()->icon());
        w->getBtn6()->setIcon(widget->getBtn6()->icon());


        w->getBtn1()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        w->getBtn2()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        w->getBtn3()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        w->getBtn4()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        w->getBtn5()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        w->getBtn4()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        w->getBtn1()->setContextMenuPolicy(Qt::CustomContextMenu);
        w->getBtn2()->setContextMenuPolicy(Qt::CustomContextMenu);
        w->getBtn3()->setContextMenuPolicy(Qt::CustomContextMenu);
        w->getBtn4()->setContextMenuPolicy(Qt::CustomContextMenu);
        w->getBtn5()->setContextMenuPolicy(Qt::CustomContextMenu);
        w->getBtn6()->setContextMenuPolicy(Qt::CustomContextMenu);

        w->getBtn1()->setText(btn1Text);
        w->getBtn2()->setText(btn2Text);
        w->getBtn3()->setText(btn3Text);
        w->getBtn4()->setText(btn4Text);
        w->getBtn5()->setText(btn5Text);
        w->getBtn6()->setText(btn6Text);

        w->getBtn1()->setToolTip(btn1ToolTip);
        w->getBtn2()->setToolTip(btn2ToolTip);
        w->getBtn3()->setToolTip(btn3ToolTip);
        w->getBtn4()->setToolTip(btn4ToolTip);
        w->getBtn5()->setToolTip(btn5ToolTip);
        w->getBtn6()->setToolTip(btn6ToolTip);

        hideButtons(w);

        connect(w,&CustomWidget::btn1Clicked,this,&CustomDelegate::slotBtn1Click);
        connect(w,&CustomWidget::btn2Clicked,this,&CustomDelegate::slotBtn2Click);
        connect(w,&CustomWidget::btn3Clicked,this,&CustomDelegate::slotBtn3Click);
        connect(w,&CustomWidget::btn4Clicked,this,&CustomDelegate::slotBtn4Click);
        connect(w,&CustomWidget::btn5Clicked,this,&CustomDelegate::slotBtn5Click);
        connect(w,&CustomWidget::btn6Clicked,this,&CustomDelegate::slotBtn6Click);

        connect(w,&CustomWidget::updButtonClicked,this,&CustomDelegate::slotUpdClick);
        connect(w,&CustomWidget::delButtonClicked,this,&CustomDelegate::slotDelClick);
        w->setObjectName("btn");
        return w;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }
}

void CustomDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void CustomDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index,editor->grab());
}


void CustomDelegate::setCustomColumn(int value)
{
    customColumn = value;
}

void CustomDelegate::hideToolButton(QToolButton *btn)
{
    widget->hideToolButton(btn);
}

void CustomDelegate::hideToolButton(const QString &objName)
{
    widget->hideToolButton(objName);
}

void CustomDelegate::hideButtons(CustomWidget *widget) const
{
    if(!buttons.isEmpty()){
        for(int i : buttons){
            switch (i) {
            case 1:
                widget->getBtn1()->setHidden(true);
                break;
            case 2:
                widget->getBtn2()->setHidden(true);
                break;
            case 3:
                widget->getBtn3()->setHidden(true);
                break;
            case 4:
                widget->getBtn4()->setHidden(true);
                break;
            case 5:
                widget->getBtn5()->setHidden(true);
                break;
            case 6:
                widget->getBtn6()->setHidden(true);
                break;
            default:
                break;
            }
        }
    }else{
        widget->getBtn1()->setHidden(true);
        widget->getBtn2()->setHidden(true);
        widget->getBtn3()->setHidden(true);
        widget->getBtn4()->setHidden(true);
        widget->getBtn5()->setHidden(true);
        widget->getBtn6()->setHidden(true);
    }

    if(!isDelBtnVisible())
        widget->getDelButton()->setHidden(true);

    if(!isUpdBtnVisible())
        widget->getUpdButton()->setHidden(true);
}

void CustomDelegate::cellEntered(const QModelIndex &index)
{
    if(index.column() == customColumn)
    {
        if(isOneCellInEditMode)
        {
            view->closePersistentEditor(currentEditedCellIndex);
        }
        view->openPersistentEditor(index);
        isOneCellInEditMode = true;
        currentEditedCellIndex = index;
    }
    else
    {
        if(isOneCellInEditMode)
        {
            isOneCellInEditMode = false;
            view->closePersistentEditor(currentEditedCellIndex);
        }
    }
}

void CustomDelegate::setBtn6ToolTip(const QString &value)
{
    btn6ToolTip = value;
    widget->getBtn6()->setToolTip(value);
}

void CustomDelegate::setBtn5ToolTip(const QString &value)
{
    btn5ToolTip = value;
    widget->getBtn5()->setToolTip(value);
}

void CustomDelegate::setBtn4ToolTip(const QString &value)
{
    btn4ToolTip = value;
    widget->getBtn4()->setToolTip(value);
}

void CustomDelegate::setBtn3ToolTip(const QString &value)
{
    btn3ToolTip = value;
    widget->getBtn3()->setToolTip(value);
}

void CustomDelegate::setBtn2ToolTip(const QString &value)
{
    btn2ToolTip = value;
    widget->getBtn2()->setToolTip(value);
}

void CustomDelegate::setBtn1ToolTip(const QString &value)
{
    btn1ToolTip = value;
    widget->getBtn1()->setToolTip(value);
}

QList<int> &CustomDelegate::getButtonsTohide()
{
    return buttons;
}

void CustomDelegate::setBtn6Text(const QString &value)
{
    btn6Text = value;
    widget->getBtn6()->setText(btn6Text);
}

void CustomDelegate::hideToolButton(bool value, int num)
{
    if(value && num > 0)
        buttons.append(num);
}

void CustomDelegate::setBtn5Text(const QString &value)
{
    btn5Text = value;
    widget->getBtn5()->setText(btn5Text);
}

void CustomDelegate::setBtn4Text(const QString &value)
{
    btn4Text = value;
    widget->getBtn4()->setText(btn4Text);
}

void CustomDelegate::setBtn3Text(const QString &value)
{
    btn3Text = value;
    widget->getBtn3()->setText(btn3Text);
}

void CustomDelegate::setBtn2Text(const QString &value)
{
    btn2Text = value;
    widget->getBtn2()->setText(btn2Text);
}

void CustomDelegate::setBtn1Text(const QString &value)
{
    btn1Text = value;
    widget->getBtn1()->setText(btn1Text);
}

bool CustomDelegate::isDelBtnVisible() const
{
    return delBtnVisible;
}

void CustomDelegate::setDelBtnVisible(bool value)
{
    delBtnVisible = value;
}

bool CustomDelegate::isUpdBtnVisible() const
{
    return updBtnVisible;
}

void CustomDelegate::setUpdBtnVisible(bool value)
{
    updBtnVisible = value;
}
